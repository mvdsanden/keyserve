// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ksvc_cryptokey.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ksvc_5fcryptokey_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ksvc_5fcryptokey_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3008000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3008000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "ksvc_cryptokeyversion.pb.h"
#include "ksvc_cryptokeyversiontemplate.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ksvc_5fcryptokey_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ksvc_5fcryptokey_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ksvc_5fcryptokey_2eproto;
namespace MvdS {
namespace ksvc {
class CryptoKey;
class CryptoKeyDefaultTypeInternal;
extern CryptoKeyDefaultTypeInternal _CryptoKey_default_instance_;
}  // namespace ksvc
}  // namespace MvdS
PROTOBUF_NAMESPACE_OPEN
template<> ::MvdS::ksvc::CryptoKey* Arena::CreateMaybeMessage<::MvdS::ksvc::CryptoKey>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace MvdS {
namespace ksvc {

// ===================================================================

class CryptoKey :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MvdS.ksvc.CryptoKey) */ {
 public:
  CryptoKey();
  virtual ~CryptoKey();

  CryptoKey(const CryptoKey& from);
  CryptoKey(CryptoKey&& from) noexcept
    : CryptoKey() {
    *this = ::std::move(from);
  }

  inline CryptoKey& operator=(const CryptoKey& from) {
    CopyFrom(from);
    return *this;
  }
  inline CryptoKey& operator=(CryptoKey&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const CryptoKey& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CryptoKey* internal_default_instance() {
    return reinterpret_cast<const CryptoKey*>(
               &_CryptoKey_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(CryptoKey* other);
  friend void swap(CryptoKey& a, CryptoKey& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CryptoKey* New() const final {
    return CreateMaybeMessage<CryptoKey>(nullptr);
  }

  CryptoKey* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<CryptoKey>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const CryptoKey& from);
  void MergeFrom(const CryptoKey& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CryptoKey* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MvdS.ksvc.CryptoKey";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ksvc_5fcryptokey_2eproto);
    return ::descriptor_table_ksvc_5fcryptokey_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const std::string& name() const;
  void set_name(const std::string& value);
  void set_name(std::string&& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  std::string* mutable_name();
  std::string* release_name();
  void set_allocated_name(std::string* name);

  // .MvdS.ksvc.CryptoKeyVersion primary = 2;
  bool has_primary() const;
  void clear_primary();
  static const int kPrimaryFieldNumber = 2;
  const ::MvdS::ksvc::CryptoKeyVersion& primary() const;
  ::MvdS::ksvc::CryptoKeyVersion* release_primary();
  ::MvdS::ksvc::CryptoKeyVersion* mutable_primary();
  void set_allocated_primary(::MvdS::ksvc::CryptoKeyVersion* primary);

  // .MvdS.ksvc.CryptoKeyVersionTemplate versionTemplate = 3;
  bool has_versiontemplate() const;
  void clear_versiontemplate();
  static const int kVersionTemplateFieldNumber = 3;
  const ::MvdS::ksvc::CryptoKeyVersionTemplate& versiontemplate() const;
  ::MvdS::ksvc::CryptoKeyVersionTemplate* release_versiontemplate();
  ::MvdS::ksvc::CryptoKeyVersionTemplate* mutable_versiontemplate();
  void set_allocated_versiontemplate(::MvdS::ksvc::CryptoKeyVersionTemplate* versiontemplate);

  // @@protoc_insertion_point(class_scope:MvdS.ksvc.CryptoKey)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  ::MvdS::ksvc::CryptoKeyVersion* primary_;
  ::MvdS::ksvc::CryptoKeyVersionTemplate* versiontemplate_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ksvc_5fcryptokey_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CryptoKey

// string name = 1;
inline void CryptoKey::clear_name() {
  name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& CryptoKey::name() const {
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CryptoKey.name)
  return name_.GetNoArena();
}
inline void CryptoKey::set_name(const std::string& value) {
  
  name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MvdS.ksvc.CryptoKey.name)
}
inline void CryptoKey::set_name(std::string&& value) {
  
  name_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MvdS.ksvc.CryptoKey.name)
}
inline void CryptoKey::set_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MvdS.ksvc.CryptoKey.name)
}
inline void CryptoKey::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MvdS.ksvc.CryptoKey.name)
}
inline std::string* CryptoKey::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:MvdS.ksvc.CryptoKey.name)
  return name_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* CryptoKey::release_name() {
  // @@protoc_insertion_point(field_release:MvdS.ksvc.CryptoKey.name)
  
  return name_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void CryptoKey::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:MvdS.ksvc.CryptoKey.name)
}

// .MvdS.ksvc.CryptoKeyVersion primary = 2;
inline bool CryptoKey::has_primary() const {
  return this != internal_default_instance() && primary_ != nullptr;
}
inline const ::MvdS::ksvc::CryptoKeyVersion& CryptoKey::primary() const {
  const ::MvdS::ksvc::CryptoKeyVersion* p = primary_;
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CryptoKey.primary)
  return p != nullptr ? *p : *reinterpret_cast<const ::MvdS::ksvc::CryptoKeyVersion*>(
      &::MvdS::ksvc::_CryptoKeyVersion_default_instance_);
}
inline ::MvdS::ksvc::CryptoKeyVersion* CryptoKey::release_primary() {
  // @@protoc_insertion_point(field_release:MvdS.ksvc.CryptoKey.primary)
  
  ::MvdS::ksvc::CryptoKeyVersion* temp = primary_;
  primary_ = nullptr;
  return temp;
}
inline ::MvdS::ksvc::CryptoKeyVersion* CryptoKey::mutable_primary() {
  
  if (primary_ == nullptr) {
    auto* p = CreateMaybeMessage<::MvdS::ksvc::CryptoKeyVersion>(GetArenaNoVirtual());
    primary_ = p;
  }
  // @@protoc_insertion_point(field_mutable:MvdS.ksvc.CryptoKey.primary)
  return primary_;
}
inline void CryptoKey::set_allocated_primary(::MvdS::ksvc::CryptoKeyVersion* primary) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(primary_);
  }
  if (primary) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      primary = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, primary, submessage_arena);
    }
    
  } else {
    
  }
  primary_ = primary;
  // @@protoc_insertion_point(field_set_allocated:MvdS.ksvc.CryptoKey.primary)
}

// .MvdS.ksvc.CryptoKeyVersionTemplate versionTemplate = 3;
inline bool CryptoKey::has_versiontemplate() const {
  return this != internal_default_instance() && versiontemplate_ != nullptr;
}
inline const ::MvdS::ksvc::CryptoKeyVersionTemplate& CryptoKey::versiontemplate() const {
  const ::MvdS::ksvc::CryptoKeyVersionTemplate* p = versiontemplate_;
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CryptoKey.versionTemplate)
  return p != nullptr ? *p : *reinterpret_cast<const ::MvdS::ksvc::CryptoKeyVersionTemplate*>(
      &::MvdS::ksvc::_CryptoKeyVersionTemplate_default_instance_);
}
inline ::MvdS::ksvc::CryptoKeyVersionTemplate* CryptoKey::release_versiontemplate() {
  // @@protoc_insertion_point(field_release:MvdS.ksvc.CryptoKey.versionTemplate)
  
  ::MvdS::ksvc::CryptoKeyVersionTemplate* temp = versiontemplate_;
  versiontemplate_ = nullptr;
  return temp;
}
inline ::MvdS::ksvc::CryptoKeyVersionTemplate* CryptoKey::mutable_versiontemplate() {
  
  if (versiontemplate_ == nullptr) {
    auto* p = CreateMaybeMessage<::MvdS::ksvc::CryptoKeyVersionTemplate>(GetArenaNoVirtual());
    versiontemplate_ = p;
  }
  // @@protoc_insertion_point(field_mutable:MvdS.ksvc.CryptoKey.versionTemplate)
  return versiontemplate_;
}
inline void CryptoKey::set_allocated_versiontemplate(::MvdS::ksvc::CryptoKeyVersionTemplate* versiontemplate) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(versiontemplate_);
  }
  if (versiontemplate) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      versiontemplate = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, versiontemplate, submessage_arena);
    }
    
  } else {
    
  }
  versiontemplate_ = versiontemplate;
  // @@protoc_insertion_point(field_set_allocated:MvdS.ksvc.CryptoKey.versionTemplate)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace ksvc
}  // namespace MvdS

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ksvc_5fcryptokey_2eproto
