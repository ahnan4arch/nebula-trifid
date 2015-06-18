//------------------------------------------------------------------------------
//  particlesystemmaterialnodeinstance.cc
//  (C) 2011-2013 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "particles/particlesystemnodeinstance.h"
#include "particles/particlesystemnode.h"
#include "coregraphics/transformdevice.h"
#include "particles/particlerenderer.h"
#include "coregraphics/shadersemantics.h"
#include "models/model.h"
#include "materials/materialinstance.h"
#include "models/modelnodeinstance.h"
#include "models/modelinstance.h"
#include "graphics/modelentity.h"
#include "coregraphics/shaderserver.h"
#include "frame/frameserver.h"
#include "particleserver.h"

namespace Particles
{
__ImplementClass(Particles::ParticleSystemNodeInstance, 'PSNI', Models::StateNodeInstance);

using namespace Models;
using namespace Util;
using namespace CoreGraphics;
using namespace Math;
using namespace Materials;
using namespace Graphics;
using namespace Frame;
using namespace Resources;

//------------------------------------------------------------------------------
/**
*/
ParticleSystemNodeInstance::ParticleSystemNodeInstance()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
ParticleSystemNodeInstance::~ParticleSystemNodeInstance()
{
    n_assert(!this->particleSystemInstance.isvalid());
}    

//------------------------------------------------------------------------------
/**
*/
void 
ParticleSystemNodeInstance::OnVisibilityResolve(IndexT resolveIndex, float distanceToViewer)
{
    // check if node is inside lod distances or if no lod is used
    const Ptr<TransformNode>& transformNode = this->modelNode.downcast<TransformNode>();
    if (transformNode->CheckLodDistance(distanceToViewer))
    {
		this->modelNode->AddVisibleNodeInstance(resolveIndex, this->material->GetMaterialType(), this);
        ModelNodeInstance::OnVisibilityResolve(resolveIndex, distanceToViewer);
    }
}

//------------------------------------------------------------------------------
/**
*/
void
ParticleSystemNodeInstance::Setup(const Ptr<ModelInstance>& inst, const Ptr<ModelNode>& node, const Ptr<ModelNodeInstance>& parentNodeInst)
{
    n_assert(!this->particleSystemInstance.isvalid());

    // up to parent class
    StateNodeInstance::Setup(inst, node, parentNodeInst);

    // setup a new particle system instance
    this->particleSystemInstance = ParticleSystemInstance::Create();
    const Ptr<ParticleSystemNode>& particleSystemNode = node.downcast<ParticleSystemNode>();

	// get mesh
	Ptr<Mesh> emitterMesh;
	if (particleSystemNode->GetEmitterMesh().isvalid())
	{
		emitterMesh = particleSystemNode->GetEmitterMesh()->GetMesh();
	}
	else
	{
		emitterMesh = ParticleServer::Instance()->GetDefaultEmitterMesh();
	}

	// setup and start particle system
    this->particleSystemInstance->Setup(emitterMesh, particleSystemNode->GetPrimitiveGroupIndex(), particleSystemNode->GetEmitterAttrs());
	this->particleSystemInstance->Start();

    // clone base material
    this->surfaceClone = this->modelNode.downcast<StateNode>()->GetMaterial();

    if (this->surfaceClone->HasConstant(NEBULA3_SEMANTIC_EMITTERTRANSFORM))
	{
        this->emitterOrientation = this->surfaceClone->GetConstant(NEBULA3_SEMANTIC_EMITTERTRANSFORM)->CreateInstance();
	}
    if (this->surfaceClone->HasConstant(NEBULA3_SEMANTIC_BILLBOARD))
	{
		this->billBoard = this->surfaceClone->GetConstant(NEBULA3_SEMANTIC_BILLBOARD)->CreateInstance();
	}
    if (this->surfaceClone->HasConstant(NEBULA3_SEMANTIC_BBOXCENTER))
	{
		this->bboxCenter = this->surfaceClone->GetConstant(NEBULA3_SEMANTIC_BBOXCENTER)->CreateInstance();
	}
    if (this->surfaceClone->HasConstant(NEBULA3_SEMANTIC_BBOXSIZE))
	{
		this->bboxSize = this->surfaceClone->GetConstant(NEBULA3_SEMANTIC_BBOXSIZE)->CreateInstance();
	}
    if (this->surfaceClone->HasConstant(NEBULA3_SEMANTIC_TIME))
	{
		this->time = this->surfaceClone->GetConstant(NEBULA3_SEMANTIC_TIME)->CreateInstance();
	}
    if (this->surfaceClone->HasConstant(NEBULA3_SEMANTIC_ANIMPHASES))
	{
		this->animPhases = this->surfaceClone->GetConstant(NEBULA3_SEMANTIC_ANIMPHASES)->CreateInstance();
	}
    if (this->surfaceClone->HasConstant(NEBULA3_SEMANTIC_ANIMSPERSEC))
	{
		this->animsPerSec = this->surfaceClone->GetConstant(NEBULA3_SEMANTIC_ANIMSPERSEC)->CreateInstance();
	}
    if (this->surfaceClone->HasConstant(NEBULA3_SEMANTIC_DEPTHBUFFER))
	{
		Ptr<FrameShader> defaultFrameShader = FrameServer::Instance()->LookupFrameShader(NEBULA3_DEFAULT_FRAMESHADER_NAME);
		Ptr<RenderTarget> depthTexture = defaultFrameShader->GetRenderTargetByName("DepthBuffer");
		this->depthBuffer = this->surfaceClone->GetConstant(NEBULA3_SEMANTIC_DEPTHBUFFER)->CreateInstance();
		this->depthBuffer->SetTexture(depthTexture->GetResolveTexture());
	}


#if __PS3__
    const Util::Array<Util::KeyValuePair<Util::StringAtom, Util::Variant> > &shaderParams = particleSystemNode->GetShaderParameter();
    IndexT i;
    int numAnimPhases = -1;
    float animFramesPerSecond = -1.0f;
    for (i = 0; i < shaderParams.Size(); i++)
    {
        if(shaderParams[i].Key() == "ALPHAREF")
        {
            numAnimPhases = shaderParams[i].Value().GetInt();
        }
        else if(shaderParams[i].Key() == "INTENSITY1")
        {
            animFramesPerSecond = shaderParams[i].Value().GetFloat();
        }
    }
    n_assert(-1 != numAnimPhases);
    n_assert(-1.0f != animFramesPerSecond);
    this->particleSystemInstance->SetNumAnimPhases(numAnimPhases);
    this->particleSystemInstance->SetAnimFramesPerSecond(animFramesPerSecond);
#endif

}

//------------------------------------------------------------------------------
/**
*/
void
ParticleSystemNodeInstance::Discard()
{
    n_assert(this->particleSystemInstance.isvalid());

    // discard material clone
	//this->surfaceClone->Unload();
	this->surfaceClone = 0;
	this->emitterOrientation->Discard();
    this->emitterOrientation = 0;
    this->billBoard = 0;
    this->bboxCenter = 0;
    this->bboxSize = 0;
    this->time = 0;
	this->animPhases->Discard();
    this->animPhases = 0;
	this->animsPerSec->Discard();
    this->animsPerSec = 0;
    this->depthBuffer = 0;

    // discard our particle system instance
    this->particleSystemInstance->Discard();
    this->particleSystemInstance = 0;

    // up to parent-class
    StateNodeInstance::Discard();
}

//------------------------------------------------------------------------------
/**
*/
void
ParticleSystemNodeInstance::OnRenderBefore(IndexT frameIndex, Timing::Time time)
{
    // call parent class
    StateNodeInstance::OnRenderBefore(frameIndex, time);    

    this->particleSystemInstance->OnRenderBefore();

    // update particle system with new model transform
    this->particleSystemInstance->SetTransform(this->modelTransform);

    // updating happens in 2 stages:
    // 1) within activity distance: particles are emitted and updated
    // 2) in view volume: particle system is added for rendering
    const point& eyePos = TransformDevice::Instance()->GetInvViewTransform().get_position();
    const point& myPos  = this->modelTransform.get_position();
    float dist = float4(myPos - eyePos).length();
    float activityDist = this->particleSystemInstance->GetParticleSystem()->GetEmitterAttrs().GetFloat(EmitterAttrs::ActivityDistance);
    if (dist <= activityDist)
    {
        // alright, we're within the activity distance, update the particle system
        this->particleSystemInstance->Update(time);

        // check if we're also in the view volume, and if yes, 
        // register the particle system for rendering
        // FIXME: use actual particle bounding box!!!
        const bbox& localBox = this->particleSystemInstance->GetBoundingBox();
		const Ptr<Graphics::ModelEntity>& modelEntity = this->modelInstance->GetModelEntity();
		modelEntity->ExtendLocalBoundingBox(localBox);
		
        /*
        // get model entity so that we can retrieve its local bounding box
        const Ptr<Graphics::ModelEntity>& modelEntity = this->modelInstance->GetModelEntity();

        // get transform from model
        // inverse transform
        // now apply to the global bounding box of the particles, the particles should now be in local space
        matrix44 trans = modelEntity->GetTransform();
        trans = matrix44::inverse(trans);
        bbox localBox = modelEntity->GetLocalBoundingBox();
        bbox localParticleBox = globalBox;
        localParticleBox.transform(trans);

        // extend with local particle box and update model entity local bounding box
        localBox.extend(localParticleBox);
        modelEntity->SetLocalBoundingBox(localBox);
        */
		
        const matrix44& viewProj = TransformDevice::Instance()->GetViewProjTransform();
		if (ClipStatus::Outside != localBox.clipstatus(viewProj))
        {
            // yes, we're visible
            ParticleRenderer::Instance()->AddVisibleParticleSystem(this->particleSystemInstance);
        }
        else
        {
            // FIXME DEBUG
            // n_printf("%f: Particle system invisible (clip) %s!\n", time, this->modelNode->GetName().Value());
        }
    }
    else
    {
        // FIXME DEBUG
        //n_printf("Particle system invisible (activity dist) %s!\n", this->modelNode->GetName().Value());
    }
}

//------------------------------------------------------------------------------
/**
*/
void
ParticleSystemNodeInstance::ApplyState(const Ptr<CoreGraphics::ShaderInstance>& shader)
{
	// set variables
	if (this->GetParticleSystemInstance()->GetParticleSystem()->GetEmitterAttrs().GetBool(EmitterAttrs::Billboard))
	{
		// use inverse view matrix for orientation 
		this->emitterOrientation->SetValue(TransformDevice::Instance()->GetInvViewTransform());
	}
	else
	{
		// otherwise, use the matrix of the particle system
        this->emitterOrientation->SetValue(this->GetParticleSystemInstance()->GetTransform());
	}

    //billBoard->SetBool(this->GetParticleSystemInstance()->GetParticleSystem()->GetEmitterAttrs().GetBool(EmitterAttrs::Billboard));	
	//this->bboxCenter->SetFloat4(this->GetParticleSystemInstance()->GetBoundingBox().center());
	//this->bboxSize->SetFloat4(this->GetParticleSystemInstance()->GetBoundingBox().extents());
    this->animPhases->SetValue(this->GetParticleSystemInstance()->GetParticleSystem()->GetEmitterAttrs().GetInt(EmitterAttrs::AnimPhases));
    this->animsPerSec->SetValue(this->GetParticleSystemInstance()->GetParticleSystem()->GetEmitterAttrs().GetFloat(EmitterAttrs::PhasesPerSecond));

	// call base class (applies time)
	StateNodeInstance::ApplyState(shader);

	this->emitterOrientation->Apply(shader);
	this->animPhases->Apply(shader);
	this->animsPerSec->Apply(shader);
	this->depthBuffer->Apply(shader);
}

//------------------------------------------------------------------------------
/**
*/
void 
ParticleSystemNodeInstance::Render()
{
    StateNodeInstance::Render();
    ParticleRenderer::Instance()->RenderParticleSystem(this->particleSystemInstance);
}

//------------------------------------------------------------------------------
/**
*/
void
ParticleSystemNodeInstance::RenderDebug()
{
    StateNodeInstance::RenderDebug();
    this->particleSystemInstance->RenderDebug();
}

//------------------------------------------------------------------------------
/**
*/
void
ParticleSystemNodeInstance::OnShow(Timing::Time time)
{
    this->particleSystemInstance->Start();
}

//------------------------------------------------------------------------------
/**
*/
void
ParticleSystemNodeInstance::OnHide(Timing::Time time)
{
    // FIXME: should stop immediately?
    if (this->particleSystemInstance->IsPlaying())
    {
        this->particleSystemInstance->Stop();
    }
}

} // namespace Particles
