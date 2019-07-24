// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ksvc_keyserveservice.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ksvc_5fkeyserveservice_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ksvc_5fkeyserveservice_2eproto

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
#include "ksvc_keyring.pb.h"
#include "ksvc_cryptokey.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ksvc_5fkeyserveservice_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ksvc_5fkeyserveservice_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ksvc_5fkeyserveservice_2eproto;
namespace MvdS {
namespace ksvc {
class CreateCryptoKeyRequest;
class CreateCryptoKeyRequestDefaultTypeInternal;
extern CreateCryptoKeyRequestDefaultTypeInternal _CreateCryptoKeyRequest_default_instance_;
class CreateKeyRingRequest;
class CreateKeyRingRequestDefaultTypeInternal;
extern CreateKeyRingRequestDefaultTypeInternal _CreateKeyRingRequest_default_instance_;
}  // namespace ksvc
}  // namespace MvdS
PROTOBUF_NAMESPACE_OPEN
template<> ::MvdS::ksvc::CreateCryptoKeyRequest* Arena::CreateMaybeMessage<::MvdS::ksvc::CreateCryptoKeyRequest>(Arena*);
template<> ::MvdS::ksvc::CreateKeyRingRequest* Arena::CreateMaybeMessage<::MvdS::ksvc::CreateKeyRingRequest>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace MvdS {
namespace ksvc {

// ===================================================================

class CreateKeyRingRequest :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MvdS.ksvc.CreateKeyRingRequest) */ {
 public:
  CreateKeyRingRequest();
  virtual ~CreateKeyRingRequest();

  CreateKeyRingRequest(const CreateKeyRingRequest& from);
  CreateKeyRingRequest(CreateKeyRingRequest&& from) noexcept
    : CreateKeyRingRequest() {
    *this = ::std::move(from);
  }

  inline CreateKeyRingRequest& operator=(const CreateKeyRingRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline CreateKeyRingRequest& operator=(CreateKeyRingRequest&& from) noexcept {
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
  static const CreateKeyRingRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CreateKeyRingRequest* internal_default_instance() {
    return reinterpret_cast<const CreateKeyRingRequest*>(
               &_CreateKeyRingRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(CreateKeyRingRequest* other);
  friend void swap(CreateKeyRingRequest& a, CreateKeyRingRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CreateKeyRingRequest* New() const final {
    return CreateMaybeMessage<CreateKeyRingRequest>(nullptr);
  }

  CreateKeyRingRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<CreateKeyRingRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const CreateKeyRingRequest& from);
  void MergeFrom(const CreateKeyRingRequest& from);
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
  void InternalSwap(CreateKeyRingRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MvdS.ksvc.CreateKeyRingRequest";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ksvc_5fkeyserveservice_2eproto);
    return ::descriptor_table_ksvc_5fkeyserveservice_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string parent = 1;
  void clear_parent();
  static const int kParentFieldNumber = 1;
  const std::string& parent() const;
  void set_parent(const std::string& value);
  void set_parent(std::string&& value);
  void set_parent(const char* value);
  void set_parent(const char* value, size_t size);
  std::string* mutable_parent();
  std::string* release_parent();
  void set_allocated_parent(std::string* parent);

  // string keyRingId = 2;
  void clear_keyringid();
  static const int kKeyRingIdFieldNumber = 2;
  const std::string& keyringid() const;
  void set_keyringid(const std::string& value);
  void set_keyringid(std::string&& value);
  void set_keyringid(const char* value);
  void set_keyringid(const char* value, size_t size);
  std::string* mutable_keyringid();
  std::string* release_keyringid();
  void set_allocated_keyringid(std::string* keyringid);

  // .MvdS.ksvc.KeyRing keyRing = 3;
  bool has_keyring() const;
  void clear_keyring();
  static const int kKeyRingFieldNumber = 3;
  const ::MvdS::ksvc::KeyRing& keyring() const;
  ::MvdS::ksvc::KeyRing* release_keyring();
  ::MvdS::ksvc::KeyRing* mutable_keyring();
  void set_allocated_keyring(::MvdS::ksvc::KeyRing* keyring);

  // @@protoc_insertion_point(class_scope:MvdS.ksvc.CreateKeyRingRequest)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr parent_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr keyringid_;
  ::MvdS::ksvc::KeyRing* keyring_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ksvc_5fkeyserveservice_2eproto;
};
// -------------------------------------------------------------------

class CreateCryptoKeyRequest :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MvdS.ksvc.CreateCryptoKeyRequest) */ {
 public:
  CreateCryptoKeyRequest();
  virtual ~CreateCryptoKeyRequest();

  CreateCryptoKeyRequest(const CreateCryptoKeyRequest& from);
  CreateCryptoKeyRequest(CreateCryptoKeyRequest&& from) noexcept
    : CreateCryptoKeyRequest() {
    *this = ::std::move(from);
  }

  inline CreateCryptoKeyRequest& operator=(const CreateCryptoKeyRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline CreateCryptoKeyRequest& operator=(CreateCryptoKeyRequest&& from) noexcept {
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
  static const CreateCryptoKeyRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CreateCryptoKeyRequest* internal_default_instance() {
    return reinterpret_cast<const CreateCryptoKeyRequest*>(
               &_CreateCryptoKeyRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(CreateCryptoKeyRequest* other);
  friend void swap(CreateCryptoKeyRequest& a, CreateCryptoKeyRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CreateCryptoKeyRequest* New() const final {
    return CreateMaybeMessage<CreateCryptoKeyRequest>(nullptr);
  }

  CreateCryptoKeyRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<CreateCryptoKeyRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const CreateCryptoKeyRequest& from);
  void MergeFrom(const CreateCryptoKeyRequest& from);
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
  void InternalSwap(CreateCryptoKeyRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MvdS.ksvc.CreateCryptoKeyRequest";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ksvc_5fkeyserveservice_2eproto);
    return ::descriptor_table_ksvc_5fkeyserveservice_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string parent = 1;
  void clear_parent();
  static const int kParentFieldNumber = 1;
  const std::string& parent() const;
  void set_parent(const std::string& value);
  void set_parent(std::string&& value);
  void set_parent(const char* value);
  void set_parent(const char* value, size_t size);
  std::string* mutable_parent();
  std::string* release_parent();
  void set_allocated_parent(std::string* parent);

  // string cryptoKeyId = 2;
  void clear_cryptokeyid();
  static const int kCryptoKeyIdFieldNumber = 2;
  const std::string& cryptokeyid() const;
  void set_cryptokeyid(const std::string& value);
  void set_cryptokeyid(std::string&& value);
  void set_cryptokeyid(const char* value);
  void set_cryptokeyid(const char* value, size_t size);
  std::string* mutable_cryptokeyid();
  std::string* release_cryptokeyid();
  void set_allocated_cryptokeyid(std::string* cryptokeyid);

  // .MvdS.ksvc.CryptoKey cryptoKey = 3;
  bool has_cryptokey() const;
  void clear_cryptokey();
  static const int kCryptoKeyFieldNumber = 3;
  const ::MvdS::ksvc::CryptoKey& cryptokey() const;
  ::MvdS::ksvc::CryptoKey* release_cryptokey();
  ::MvdS::ksvc::CryptoKey* mutable_cryptokey();
  void set_allocated_cryptokey(::MvdS::ksvc::CryptoKey* cryptokey);

  // bool skipInitialVersionCreation = 4;
  void clear_skipinitialversioncreation();
  static const int kSkipInitialVersionCreationFieldNumber = 4;
  bool skipinitialversioncreation() const;
  void set_skipinitialversioncreation(bool value);

  // @@protoc_insertion_point(class_scope:MvdS.ksvc.CreateCryptoKeyRequest)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr parent_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr cryptokeyid_;
  ::MvdS::ksvc::CryptoKey* cryptokey_;
  bool skipinitialversioncreation_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ksvc_5fkeyserveservice_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CreateKeyRingRequest

// string parent = 1;
inline void CreateKeyRingRequest::clear_parent() {
  parent_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& CreateKeyRingRequest::parent() const {
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CreateKeyRingRequest.parent)
  return parent_.GetNoArena();
}
inline void CreateKeyRingRequest::set_parent(const std::string& value) {
  
  parent_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MvdS.ksvc.CreateKeyRingRequest.parent)
}
inline void CreateKeyRingRequest::set_parent(std::string&& value) {
  
  parent_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MvdS.ksvc.CreateKeyRingRequest.parent)
}
inline void CreateKeyRingRequest::set_parent(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  parent_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MvdS.ksvc.CreateKeyRingRequest.parent)
}
inline void CreateKeyRingRequest::set_parent(const char* value, size_t size) {
  
  parent_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MvdS.ksvc.CreateKeyRingRequest.parent)
}
inline std::string* CreateKeyRingRequest::mutable_parent() {
  
  // @@protoc_insertion_point(field_mutable:MvdS.ksvc.CreateKeyRingRequest.parent)
  return parent_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* CreateKeyRingRequest::release_parent() {
  // @@protoc_insertion_point(field_release:MvdS.ksvc.CreateKeyRingRequest.parent)
  
  return parent_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void CreateKeyRingRequest::set_allocated_parent(std::string* parent) {
  if (parent != nullptr) {
    
  } else {
    
  }
  parent_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), parent);
  // @@protoc_insertion_point(field_set_allocated:MvdS.ksvc.CreateKeyRingRequest.parent)
}

// string keyRingId = 2;
inline void CreateKeyRingRequest::clear_keyringid() {
  keyringid_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& CreateKeyRingRequest::keyringid() const {
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CreateKeyRingRequest.keyRingId)
  return keyringid_.GetNoArena();
}
inline void CreateKeyRingRequest::set_keyringid(const std::string& value) {
  
  keyringid_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MvdS.ksvc.CreateKeyRingRequest.keyRingId)
}
inline void CreateKeyRingRequest::set_keyringid(std::string&& value) {
  
  keyringid_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MvdS.ksvc.CreateKeyRingRequest.keyRingId)
}
inline void CreateKeyRingRequest::set_keyringid(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  keyringid_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MvdS.ksvc.CreateKeyRingRequest.keyRingId)
}
inline void CreateKeyRingRequest::set_keyringid(const char* value, size_t size) {
  
  keyringid_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MvdS.ksvc.CreateKeyRingRequest.keyRingId)
}
inline std::string* CreateKeyRingRequest::mutable_keyringid() {
  
  // @@protoc_insertion_point(field_mutable:MvdS.ksvc.CreateKeyRingRequest.keyRingId)
  return keyringid_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* CreateKeyRingRequest::release_keyringid() {
  // @@protoc_insertion_point(field_release:MvdS.ksvc.CreateKeyRingRequest.keyRingId)
  
  return keyringid_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void CreateKeyRingRequest::set_allocated_keyringid(std::string* keyringid) {
  if (keyringid != nullptr) {
    
  } else {
    
  }
  keyringid_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), keyringid);
  // @@protoc_insertion_point(field_set_allocated:MvdS.ksvc.CreateKeyRingRequest.keyRingId)
}

// .MvdS.ksvc.KeyRing keyRing = 3;
inline bool CreateKeyRingRequest::has_keyring() const {
  return this != internal_default_instance() && keyring_ != nullptr;
}
inline const ::MvdS::ksvc::KeyRing& CreateKeyRingRequest::keyring() const {
  const ::MvdS::ksvc::KeyRing* p = keyring_;
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CreateKeyRingRequest.keyRing)
  return p != nullptr ? *p : *reinterpret_cast<const ::MvdS::ksvc::KeyRing*>(
      &::MvdS::ksvc::_KeyRing_default_instance_);
}
inline ::MvdS::ksvc::KeyRing* CreateKeyRingRequest::release_keyring() {
  // @@protoc_insertion_point(field_release:MvdS.ksvc.CreateKeyRingRequest.keyRing)
  
  ::MvdS::ksvc::KeyRing* temp = keyring_;
  keyring_ = nullptr;
  return temp;
}
inline ::MvdS::ksvc::KeyRing* CreateKeyRingRequest::mutable_keyring() {
  
  if (keyring_ == nullptr) {
    auto* p = CreateMaybeMessage<::MvdS::ksvc::KeyRing>(GetArenaNoVirtual());
    keyring_ = p;
  }
  // @@protoc_insertion_point(field_mutable:MvdS.ksvc.CreateKeyRingRequest.keyRing)
  return keyring_;
}
inline void CreateKeyRingRequest::set_allocated_keyring(::MvdS::ksvc::KeyRing* keyring) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(keyring_);
  }
  if (keyring) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      keyring = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, keyring, submessage_arena);
    }
    
  } else {
    
  }
  keyring_ = keyring;
  // @@protoc_insertion_point(field_set_allocated:MvdS.ksvc.CreateKeyRingRequest.keyRing)
}

// -------------------------------------------------------------------

// CreateCryptoKeyRequest

// string parent = 1;
inline void CreateCryptoKeyRequest::clear_parent() {
  parent_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& CreateCryptoKeyRequest::parent() const {
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CreateCryptoKeyRequest.parent)
  return parent_.GetNoArena();
}
inline void CreateCryptoKeyRequest::set_parent(const std::string& value) {
  
  parent_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MvdS.ksvc.CreateCryptoKeyRequest.parent)
}
inline void CreateCryptoKeyRequest::set_parent(std::string&& value) {
  
  parent_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MvdS.ksvc.CreateCryptoKeyRequest.parent)
}
inline void CreateCryptoKeyRequest::set_parent(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  parent_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MvdS.ksvc.CreateCryptoKeyRequest.parent)
}
inline void CreateCryptoKeyRequest::set_parent(const char* value, size_t size) {
  
  parent_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MvdS.ksvc.CreateCryptoKeyRequest.parent)
}
inline std::string* CreateCryptoKeyRequest::mutable_parent() {
  
  // @@protoc_insertion_point(field_mutable:MvdS.ksvc.CreateCryptoKeyRequest.parent)
  return parent_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* CreateCryptoKeyRequest::release_parent() {
  // @@protoc_insertion_point(field_release:MvdS.ksvc.CreateCryptoKeyRequest.parent)
  
  return parent_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void CreateCryptoKeyRequest::set_allocated_parent(std::string* parent) {
  if (parent != nullptr) {
    
  } else {
    
  }
  parent_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), parent);
  // @@protoc_insertion_point(field_set_allocated:MvdS.ksvc.CreateCryptoKeyRequest.parent)
}

// string cryptoKeyId = 2;
inline void CreateCryptoKeyRequest::clear_cryptokeyid() {
  cryptokeyid_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& CreateCryptoKeyRequest::cryptokeyid() const {
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKeyId)
  return cryptokeyid_.GetNoArena();
}
inline void CreateCryptoKeyRequest::set_cryptokeyid(const std::string& value) {
  
  cryptokeyid_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKeyId)
}
inline void CreateCryptoKeyRequest::set_cryptokeyid(std::string&& value) {
  
  cryptokeyid_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKeyId)
}
inline void CreateCryptoKeyRequest::set_cryptokeyid(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  cryptokeyid_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKeyId)
}
inline void CreateCryptoKeyRequest::set_cryptokeyid(const char* value, size_t size) {
  
  cryptokeyid_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKeyId)
}
inline std::string* CreateCryptoKeyRequest::mutable_cryptokeyid() {
  
  // @@protoc_insertion_point(field_mutable:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKeyId)
  return cryptokeyid_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* CreateCryptoKeyRequest::release_cryptokeyid() {
  // @@protoc_insertion_point(field_release:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKeyId)
  
  return cryptokeyid_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void CreateCryptoKeyRequest::set_allocated_cryptokeyid(std::string* cryptokeyid) {
  if (cryptokeyid != nullptr) {
    
  } else {
    
  }
  cryptokeyid_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), cryptokeyid);
  // @@protoc_insertion_point(field_set_allocated:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKeyId)
}

// .MvdS.ksvc.CryptoKey cryptoKey = 3;
inline bool CreateCryptoKeyRequest::has_cryptokey() const {
  return this != internal_default_instance() && cryptokey_ != nullptr;
}
inline const ::MvdS::ksvc::CryptoKey& CreateCryptoKeyRequest::cryptokey() const {
  const ::MvdS::ksvc::CryptoKey* p = cryptokey_;
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKey)
  return p != nullptr ? *p : *reinterpret_cast<const ::MvdS::ksvc::CryptoKey*>(
      &::MvdS::ksvc::_CryptoKey_default_instance_);
}
inline ::MvdS::ksvc::CryptoKey* CreateCryptoKeyRequest::release_cryptokey() {
  // @@protoc_insertion_point(field_release:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKey)
  
  ::MvdS::ksvc::CryptoKey* temp = cryptokey_;
  cryptokey_ = nullptr;
  return temp;
}
inline ::MvdS::ksvc::CryptoKey* CreateCryptoKeyRequest::mutable_cryptokey() {
  
  if (cryptokey_ == nullptr) {
    auto* p = CreateMaybeMessage<::MvdS::ksvc::CryptoKey>(GetArenaNoVirtual());
    cryptokey_ = p;
  }
  // @@protoc_insertion_point(field_mutable:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKey)
  return cryptokey_;
}
inline void CreateCryptoKeyRequest::set_allocated_cryptokey(::MvdS::ksvc::CryptoKey* cryptokey) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(cryptokey_);
  }
  if (cryptokey) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      cryptokey = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, cryptokey, submessage_arena);
    }
    
  } else {
    
  }
  cryptokey_ = cryptokey;
  // @@protoc_insertion_point(field_set_allocated:MvdS.ksvc.CreateCryptoKeyRequest.cryptoKey)
}

// bool skipInitialVersionCreation = 4;
inline void CreateCryptoKeyRequest::clear_skipinitialversioncreation() {
  skipinitialversioncreation_ = false;
}
inline bool CreateCryptoKeyRequest::skipinitialversioncreation() const {
  // @@protoc_insertion_point(field_get:MvdS.ksvc.CreateCryptoKeyRequest.skipInitialVersionCreation)
  return skipinitialversioncreation_;
}
inline void CreateCryptoKeyRequest::set_skipinitialversioncreation(bool value) {
  
  skipinitialversioncreation_ = value;
  // @@protoc_insertion_point(field_set:MvdS.ksvc.CreateCryptoKeyRequest.skipInitialVersionCreation)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace ksvc
}  // namespace MvdS

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ksvc_5fkeyserveservice_2eproto
