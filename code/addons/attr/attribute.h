#pragma once
//------------------------------------------------------------------------------
/**
    @class Attr::Attribute
  
    A compiletime-typesafe key/value pair.
    
    (C) 2006 Radon Labs GmbH
    (C) 2013-2016 Individual contributors, see AUTHORS file
*/
#include "attr/boolattrid.h"
#include "attr/floatattrid.h"
#include "attr/intattrid.h"
#include "attr/matrix44attrid.h"
#include "attr/float4attrid.h"
#include "attr/stringattrid.h"
#include "attr/guidattrid.h"
#include "attr/blobattrid.h"
#include "util/variant.h"
#include "math/float4.h"
#include "math/matrix44.h"
#include "util/keyvaluepair.h"
#include "util/guid.h"
#include "util/blob.h"

//------------------------------------------------------------------------------
namespace Attr
{
class Attribute : public Util::KeyValuePair<AttrId,Util::Variant>
{
public:
    /// default constructor
    Attribute();
    /// copy constructor
    Attribute(const Attribute& rhs);
    /// construct from typeless attribute id
    Attribute(const AttrId& id);
    /// construct from bool
    Attribute(const BoolAttrId& id, bool val);
    /// construct from float
    Attribute(const FloatAttrId& id, float val);
    /// construct from int
    Attribute(const IntAttrId& id, int val);
    /// construct from matrix44
    Attribute(const Matrix44AttrId& id, const Math::matrix44& val);
    /// construct from string
    Attribute(const StringAttrId& id, const Util::String& val);
    /// construct from float4
    Attribute(const Float4AttrId& id, const Math::float4& val);
    /// construct from guid
    Attribute(const GuidAttrId& id, const Util::Guid& val);
    /// construct from blob
    Attribute(const BlobAttrId& id, const Util::Blob& val);

    /// set attribute id
    void SetAttrId(const AttrId& id);
    /// get attribute id
    const AttrId& GetAttrId() const;
    /// get name of attribute
    const Util::String& GetName() const;
    /// get fourcc of attribute
    const Util::FourCC& GetFourCC() const;
    /// get value type of attribute
    ValueType GetValueType() const;
    /// get access mode of attribute
    AccessMode GetAccessMode() const;
    /// clear the attribute's value
    void Clear();

    /// assignment operator
    void operator=(const Attribute& rhs);
    /// bool assignment operator
    void operator=(bool rhs);
    /// float assignment operator
    void operator=(float rhs);
    /// int assignment operator
    void operator=(int rhs);
    /// matrix44 assignment operator
    void operator=(const Math::matrix44& rhs);
    /// string assignment operator
    void operator=(const Util::String& rhs);
    /// float4 assignment operator
    void operator=(const Math::float4& rhs);
    /// guid assignment operator
    void operator=(const Util::Guid& rhs);
    /// blob assignment operator
    void operator=(const Util::Blob& rhs);

    /// equality operator
    bool operator==(const Attribute& rhs) const;
    /// string equality operator
    bool operator==(const Util::String& rhs) const;
    /// int equality operator
    bool operator==(int rhs) const;
    /// float equality operator
    bool operator==(float rhs) const;
    /// bool equality operator
    bool operator==(bool rhs) const;
    /// float4 equality operator
    bool operator==(const Math::float4& rhs) const;
    /// guid equality operator
    bool operator==(const Util::Guid& rhs) const;

    /// equality operator
    bool operator!=(const Attribute& rhs) const;
    /// string equality operator
    bool operator!=(const Util::String& rhs) const;
    /// int equality operator
    bool operator!=(int rhs) const;
    /// float equality operator
    bool operator!=(float rhs) const;
    /// bool equality operator
    bool operator!=(bool rhs) const;
    /// float4 equality operator
    bool operator!=(const Math::float4& rhs) const;
    /// guid equality operator
    bool operator!=(const Util::Guid& rhs) const;

    /// set bool content
    void SetBool(bool val);
    /// get bool content
    bool GetBool() const;
    /// set int content
    void SetInt(int val);
    /// get int content
    int GetInt() const;
    /// set float content
    void SetFloat(float val);
    /// get float content
    float GetFloat() const;
    /// set string content
    void SetString(const Util::String& val);
    /// get string content
    const Util::String& GetString() const;
    /// set matrix44 value
    void SetMatrix44(const Math::matrix44& val);
    /// get matrix44 value
    const Math::matrix44& GetMatrix44() const;
    /// set float4 value
    void SetFloat4(const Math::float4& val);
    /// get float4 value
    Math::float4 GetFloat4() const;
    /// set guid value
    void SetGuid(const Util::Guid& val);
    /// get guid value
    const Util::Guid& GetGuid() const;
    /// set blob value
    void SetBlob(const Util::Blob& val);
    /// get blob value
    const Util::Blob& GetBlob() const;
    /// set generic value
    void SetValue(const Util::Variant& val);
    /// get generic value
    const Util::Variant& GetValue() const;

    /// set value from string (convert as necessary)
    void SetValueFromString(const Util::String& str);
    /// convert the content to a string
    Util::String ValueAsString() const;
    /// convert string to type
    static ValueType StringToValueType(const Util::String& s);
    /// convert type to string
    static Util::String ValueTypeToString(ValueType t);
};

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const Attribute& rhs) :
    Util::KeyValuePair<AttrId,Util::Variant>(rhs.keyData, rhs.valueData)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const AttrId& id) :
    Util::KeyValuePair<AttrId,Util::Variant>(id)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const BoolAttrId& id, bool val) :
    Util::KeyValuePair<AttrId,Util::Variant>(id, Util::Variant(val))
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const FloatAttrId& id, float val) :
    Util::KeyValuePair<AttrId,Util::Variant>(id, Util::Variant(val))
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const IntAttrId& id, int val) :
    Util::KeyValuePair<AttrId,Util::Variant>(id, Util::Variant(val))
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const Matrix44AttrId& id, const Math::matrix44& val) :
    Util::KeyValuePair<AttrId,Util::Variant>(id, Util::Variant(val))
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const StringAttrId& id, const Util::String& val) :
    Util::KeyValuePair<AttrId,Util::Variant>(id, Util::Variant(val))
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const Float4AttrId& id, const Math::float4& val) :
    Util::KeyValuePair<AttrId,Util::Variant>(id, Util::Variant(val))
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const GuidAttrId& id, const Util::Guid& val) :
    Util::KeyValuePair<AttrId,Util::Variant>(id, Util::Variant(val))
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Attribute::Attribute(const BlobAttrId& id, const Util::Blob& val) :
    Util::KeyValuePair<AttrId,Util::Variant>(id, Util::Variant(val))
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetAttrId(const AttrId& id)
{
    this->keyData = id;
}

//------------------------------------------------------------------------------
/**
*/
inline const AttrId&
Attribute::GetAttrId() const
{
    return this->keyData;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
Attribute::GetName() const
{
    return this->keyData.GetName();
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::FourCC&
Attribute::GetFourCC() const
{
    return this->keyData.GetFourCC();
}

//------------------------------------------------------------------------------
/**
*/
inline ValueType
Attribute::GetValueType() const
{
    return this->keyData.GetValueType();
}

//------------------------------------------------------------------------------
/**
*/
inline AccessMode
Attribute::GetAccessMode() const
{
    return this->keyData.GetAccessMode();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::Clear()
{
    this->valueData.Clear();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::operator=(const Attribute& rhs)
{
    this->keyData = rhs.keyData;
    this->valueData = rhs.valueData;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::operator=(bool rhs)
{
    n_assert(this->GetValueType() == BoolType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::operator=(float rhs)
{
    n_assert(this->GetValueType() == FloatType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::operator=(int rhs)
{
    n_assert(this->GetValueType() == IntType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::operator=(const Math::matrix44& rhs)
{
    n_assert(this->GetValueType() == Matrix44Type);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::operator=(const Util::String& rhs)
{
    n_assert(this->GetValueType() == StringType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::operator=(const Math::float4& rhs)
{
    n_assert(this->GetValueType() == Float4Type);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::operator=(const Util::Guid& rhs)
{
    n_assert(this->GetValueType() == GuidType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::operator=(const Util::Blob& rhs)
{
    n_assert(this->GetValueType() == BlobType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator==(const Attribute& rhs) const
{
    return ((this->keyData == rhs.keyData) && (this->valueData == rhs.valueData));
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator==(const Util::String& rhs) const
{
    n_assert(this->GetValueType() == StringType);
    return this->valueData == rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator==(int rhs) const
{
    n_assert(this->GetValueType() == IntType);
    return this->valueData == rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator==(float rhs) const
{
    n_assert(this->GetValueType() == FloatType);
    return this->valueData == rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator==(bool rhs) const
{
    n_assert(this->GetValueType() == BoolType);
    return this->valueData == rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator==(const Math::float4& rhs) const
{
    n_assert(this->GetValueType() == Float4Type);
    return this->valueData == rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator==(const Util::Guid& rhs) const
{
    n_assert(this->GetValueType() == GuidType);
    return this->valueData == rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator!=(const Attribute& rhs) const
{
    return (this->keyData != rhs.keyData) || (this->valueData != rhs.valueData);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator!=(const Util::String& rhs) const
{
    n_assert(this->GetValueType() == StringType);
    return this->valueData != rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator!=(int rhs) const
{
    n_assert(this->GetValueType() == IntType);
    return this->valueData != rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator!=(float rhs) const
{
    n_assert(this->GetValueType() == FloatType);
    return this->valueData != rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator!=(const Math::float4& rhs) const
{
    n_assert(this->GetValueType() == Float4Type);
    return this->valueData != rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::operator!=(const Util::Guid& rhs) const
{
    n_assert(this->GetValueType() == GuidType);
    return this->valueData != rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetBool(bool val)
{
    n_assert(this->GetValueType() == BoolType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = val;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Attribute::GetBool() const
{
    n_assert(this->GetValueType() == BoolType);
    return this->valueData.GetBool();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetInt(int val)
{
    n_assert(this->GetValueType() == IntType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = val;
}

//------------------------------------------------------------------------------
/**
*/
inline int
Attribute::GetInt() const
{
    n_assert(this->GetValueType() == IntType);
    return this->valueData.GetInt();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetFloat(float val)
{
    n_assert(this->GetValueType() == FloatType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = val;
}

//------------------------------------------------------------------------------
/**
*/
inline float
Attribute::GetFloat() const
{
    n_assert(this->GetValueType() == FloatType);
    return this->valueData.GetFloat();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetString(const Util::String& val)
{
    n_assert(this->GetValueType() == StringType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = val;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
Attribute::GetString() const
{
    n_assert(this->GetValueType() == StringType);
    return this->valueData.GetString();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetMatrix44(const Math::matrix44& val)
{
    n_assert(this->GetValueType() == Matrix44Type);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = val;
}

//------------------------------------------------------------------------------
/**
*/
inline const Math::matrix44&
Attribute::GetMatrix44() const
{
    n_assert(this->GetValueType() == Matrix44Type);
    return this->valueData.GetMatrix44();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetFloat4(const Math::float4& val)
{
    n_assert(this->GetValueType() == Float4Type);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = val;
}

//------------------------------------------------------------------------------
/**
*/
inline Math::float4
Attribute::GetFloat4() const
{
    n_assert(this->GetValueType() == Float4Type);
    return this->valueData.GetFloat4();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetGuid(const Util::Guid& val)
{
    n_assert(this->GetValueType() == GuidType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = val;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::Guid&
Attribute::GetGuid() const
{
    n_assert(this->GetValueType() == GuidType);
    return this->valueData.GetGuid();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetBlob(const Util::Blob& val)
{
    n_assert(this->GetValueType() == BlobType);
    n_assert(this->GetAccessMode() == ReadWrite);
    this->valueData = val;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::Blob&
Attribute::GetBlob() const
{
    n_assert(this->GetValueType() == BlobType);
    return this->valueData.GetBlob();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetValueFromString(const Util::String& str)
{
    n_assert(this->GetValueType() != VoidType);
    switch (this->GetValueType())
    {
        case IntType:
            this->valueData = str.AsInt();
            break;

        case FloatType:
            this->valueData = str.AsFloat();
            break;

        case BoolType:
            this->valueData = str.AsBool();
            break;

        case Float4Type:
            this->valueData = str.AsFloat4();
            break;

        case StringType:
            this->valueData = str;
            break;

        case Matrix44Type:
            this->valueData = str.AsMatrix44();
            break;

        case GuidType:
            this->valueData = Util::Guid::FromString(str);
            break;

        default:
            n_error("Attribute::SetValueFromString(): cannot convert string to attribute type!");
            break;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline Util::String
Attribute::ValueAsString() const
{
    n_assert(this->GetValueType() != VoidType);
    Util::String str;
    switch (this->GetValueType())
    {
        case IntType:
            str.SetInt(this->GetInt());
            break;

        case FloatType:
            str.SetFloat(this->GetFloat());
            break;

        case BoolType:
            str.SetBool(this->GetBool());
            break;

        case Float4Type:
            str.SetFloat4(this->GetFloat4());
            break;

        case StringType:
            str = this->GetString();
            break;

        case Matrix44Type:
            str.SetMatrix44(this->GetMatrix44());
            break;

        case GuidType:
            str = this->GetGuid().AsString();
            break;

        case BlobType:
            n_error("Attribute: Cannot convert blob to string (attrid='%s')!", this->GetName().AsCharPtr());
            break;

        case VoidType:
            n_error("Attribute: Cannot convert void attribute to string (attrid='%s')!", this->GetName().AsCharPtr());
            break;
    }
    return str;
}

//------------------------------------------------------------------------------
/**
*/
inline ValueType
Attribute::StringToValueType(const Util::String& s)
{
    return (ValueType) Util::Variant::StringToType(s);
}

//------------------------------------------------------------------------------
/**
*/
inline Util::String
Attribute::ValueTypeToString(ValueType t)
{
    return Util::Variant::TypeToString((Util::Variant::Type)t);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Attribute::SetValue(const Util::Variant& val)
{
    this->valueData = val;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::Variant&
Attribute::GetValue() const
{
    return this->valueData;
}

} // namespace Attr
//------------------------------------------------------------------------------
