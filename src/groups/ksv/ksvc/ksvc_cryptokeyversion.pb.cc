// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ksvc_cryptokeyversion.proto

#include "ksvc_cryptokeyversion.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace MvdS {
namespace ksvc {
class CryptoKeyVersionDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<CryptoKeyVersion> _instance;
} _CryptoKeyVersion_default_instance_;
}  // namespace ksvc
}  // namespace MvdS
static void InitDefaultsscc_info_CryptoKeyVersion_ksvc_5fcryptokeyversion_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::MvdS::ksvc::_CryptoKeyVersion_default_instance_;
    new (ptr) ::MvdS::ksvc::CryptoKeyVersion();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::MvdS::ksvc::CryptoKeyVersion::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_CryptoKeyVersion_ksvc_5fcryptokeyversion_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_CryptoKeyVersion_ksvc_5fcryptokeyversion_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_ksvc_5fcryptokeyversion_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_ksvc_5fcryptokeyversion_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_ksvc_5fcryptokeyversion_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_ksvc_5fcryptokeyversion_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::MvdS::ksvc::CryptoKeyVersion, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::MvdS::ksvc::CryptoKeyVersion, name_),
  PROTOBUF_FIELD_OFFSET(::MvdS::ksvc::CryptoKeyVersion, algorithm_),
  PROTOBUF_FIELD_OFFSET(::MvdS::ksvc::CryptoKeyVersion, createtime_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::MvdS::ksvc::CryptoKeyVersion)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::MvdS::ksvc::_CryptoKeyVersion_default_instance_),
};

const char descriptor_table_protodef_ksvc_5fcryptokeyversion_2eproto[] =
  "\n\033ksvc_cryptokeyversion.proto\022\tMvdS.ksvc"
  "\032$ksvc_cryptokeyversionalgorithm.proto\"m"
  "\n\020CryptoKeyVersion\022\014\n\004name\030\001 \001(\t\0227\n\talgo"
  "rithm\030\002 \001(\0162$.MvdS.ksvc.CryptoKeyVersion"
  "Algorithm\022\022\n\ncreateTime\030\003 \001(\tb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_ksvc_5fcryptokeyversion_2eproto_deps[1] = {
  &::descriptor_table_ksvc_5fcryptokeyversionalgorithm_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_ksvc_5fcryptokeyversion_2eproto_sccs[1] = {
  &scc_info_CryptoKeyVersion_ksvc_5fcryptokeyversion_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_ksvc_5fcryptokeyversion_2eproto_once;
static bool descriptor_table_ksvc_5fcryptokeyversion_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ksvc_5fcryptokeyversion_2eproto = {
  &descriptor_table_ksvc_5fcryptokeyversion_2eproto_initialized, descriptor_table_protodef_ksvc_5fcryptokeyversion_2eproto, "ksvc_cryptokeyversion.proto", 197,
  &descriptor_table_ksvc_5fcryptokeyversion_2eproto_once, descriptor_table_ksvc_5fcryptokeyversion_2eproto_sccs, descriptor_table_ksvc_5fcryptokeyversion_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_ksvc_5fcryptokeyversion_2eproto::offsets,
  file_level_metadata_ksvc_5fcryptokeyversion_2eproto, 1, file_level_enum_descriptors_ksvc_5fcryptokeyversion_2eproto, file_level_service_descriptors_ksvc_5fcryptokeyversion_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_ksvc_5fcryptokeyversion_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_ksvc_5fcryptokeyversion_2eproto), true);
namespace MvdS {
namespace ksvc {

// ===================================================================

void CryptoKeyVersion::InitAsDefaultInstance() {
}
class CryptoKeyVersion::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int CryptoKeyVersion::kNameFieldNumber;
const int CryptoKeyVersion::kAlgorithmFieldNumber;
const int CryptoKeyVersion::kCreateTimeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

CryptoKeyVersion::CryptoKeyVersion()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MvdS.ksvc.CryptoKeyVersion)
}
CryptoKeyVersion::CryptoKeyVersion(const CryptoKeyVersion& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.name().size() > 0) {
    name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  createtime_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.createtime().size() > 0) {
    createtime_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.createtime_);
  }
  algorithm_ = from.algorithm_;
  // @@protoc_insertion_point(copy_constructor:MvdS.ksvc.CryptoKeyVersion)
}

void CryptoKeyVersion::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_CryptoKeyVersion_ksvc_5fcryptokeyversion_2eproto.base);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  createtime_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  algorithm_ = 0;
}

CryptoKeyVersion::~CryptoKeyVersion() {
  // @@protoc_insertion_point(destructor:MvdS.ksvc.CryptoKeyVersion)
  SharedDtor();
}

void CryptoKeyVersion::SharedDtor() {
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  createtime_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void CryptoKeyVersion::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const CryptoKeyVersion& CryptoKeyVersion::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_CryptoKeyVersion_ksvc_5fcryptokeyversion_2eproto.base);
  return *internal_default_instance();
}


void CryptoKeyVersion::Clear() {
// @@protoc_insertion_point(message_clear_start:MvdS.ksvc.CryptoKeyVersion)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  createtime_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  algorithm_ = 0;
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* CryptoKeyVersion::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParserUTF8(mutable_name(), ptr, ctx, "MvdS.ksvc.CryptoKeyVersion.name");
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .MvdS.ksvc.CryptoKeyVersionAlgorithm algorithm = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          set_algorithm(static_cast<::MvdS::ksvc::CryptoKeyVersionAlgorithm>(val));
        } else goto handle_unusual;
        continue;
      // string createTime = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParserUTF8(mutable_createtime(), ptr, ctx, "MvdS.ksvc.CryptoKeyVersion.createTime");
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool CryptoKeyVersion::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:MvdS.ksvc.CryptoKeyVersion)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string name = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
            this->name().data(), static_cast<int>(this->name().length()),
            ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE,
            "MvdS.ksvc.CryptoKeyVersion.name"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .MvdS.ksvc.CryptoKeyVersionAlgorithm algorithm = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (16 & 0xFF)) {
          int value = 0;
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   int, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_algorithm(static_cast< ::MvdS::ksvc::CryptoKeyVersionAlgorithm >(value));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string createTime = 3;
      case 3: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (26 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_createtime()));
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
            this->createtime().data(), static_cast<int>(this->createtime().length()),
            ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE,
            "MvdS.ksvc.CryptoKeyVersion.createTime"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:MvdS.ksvc.CryptoKeyVersion)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MvdS.ksvc.CryptoKeyVersion)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void CryptoKeyVersion::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MvdS.ksvc.CryptoKeyVersion)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string name = 1;
  if (this->name().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->name().data(), static_cast<int>(this->name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MvdS.ksvc.CryptoKeyVersion.name");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->name(), output);
  }

  // .MvdS.ksvc.CryptoKeyVersionAlgorithm algorithm = 2;
  if (this->algorithm() != 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnum(
      2, this->algorithm(), output);
  }

  // string createTime = 3;
  if (this->createtime().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->createtime().data(), static_cast<int>(this->createtime().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MvdS.ksvc.CryptoKeyVersion.createTime");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->createtime(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MvdS.ksvc.CryptoKeyVersion)
}

::PROTOBUF_NAMESPACE_ID::uint8* CryptoKeyVersion::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:MvdS.ksvc.CryptoKeyVersion)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string name = 1;
  if (this->name().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->name().data(), static_cast<int>(this->name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MvdS.ksvc.CryptoKeyVersion.name");
    target =
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // .MvdS.ksvc.CryptoKeyVersionAlgorithm algorithm = 2;
  if (this->algorithm() != 0) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      2, this->algorithm(), target);
  }

  // string createTime = 3;
  if (this->createtime().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->createtime().data(), static_cast<int>(this->createtime().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MvdS.ksvc.CryptoKeyVersion.createTime");
    target =
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
        3, this->createtime(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MvdS.ksvc.CryptoKeyVersion)
  return target;
}

size_t CryptoKeyVersion::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MvdS.ksvc.CryptoKeyVersion)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string name = 1;
  if (this->name().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->name());
  }

  // string createTime = 3;
  if (this->createtime().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->createtime());
  }

  // .MvdS.ksvc.CryptoKeyVersionAlgorithm algorithm = 2;
  if (this->algorithm() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->algorithm());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void CryptoKeyVersion::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:MvdS.ksvc.CryptoKeyVersion)
  GOOGLE_DCHECK_NE(&from, this);
  const CryptoKeyVersion* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<CryptoKeyVersion>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:MvdS.ksvc.CryptoKeyVersion)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:MvdS.ksvc.CryptoKeyVersion)
    MergeFrom(*source);
  }
}

void CryptoKeyVersion::MergeFrom(const CryptoKeyVersion& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:MvdS.ksvc.CryptoKeyVersion)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.name().size() > 0) {

    name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  if (from.createtime().size() > 0) {

    createtime_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.createtime_);
  }
  if (from.algorithm() != 0) {
    set_algorithm(from.algorithm());
  }
}

void CryptoKeyVersion::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:MvdS.ksvc.CryptoKeyVersion)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CryptoKeyVersion::CopyFrom(const CryptoKeyVersion& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MvdS.ksvc.CryptoKeyVersion)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CryptoKeyVersion::IsInitialized() const {
  return true;
}

void CryptoKeyVersion::Swap(CryptoKeyVersion* other) {
  if (other == this) return;
  InternalSwap(other);
}
void CryptoKeyVersion::InternalSwap(CryptoKeyVersion* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  name_.Swap(&other->name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  createtime_.Swap(&other->createtime_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(algorithm_, other->algorithm_);
}

::PROTOBUF_NAMESPACE_ID::Metadata CryptoKeyVersion::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace ksvc
}  // namespace MvdS
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::MvdS::ksvc::CryptoKeyVersion* Arena::CreateMaybeMessage< ::MvdS::ksvc::CryptoKeyVersion >(Arena* arena) {
  return Arena::CreateInternal< ::MvdS::ksvc::CryptoKeyVersion >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
