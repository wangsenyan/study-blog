#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include "node_union_bytes.h"
#include "v8.h"
using NativeModuleRecordMap = std::map<std::string, UnionBytes>;
using NativeModuleCacheMap =
    std::unordered_map<std::string,
                       std::unique_ptr<v8::ScriptCompiler::CachedData>>;
class MutexBase
{
private:
  mutable typename Traits::MutexT mutex_;
};
using Mutex = MutexBase<LibuvMutexTraits>;
template <typename T>
class FactoryBase;
class Factory : public FactoryBase<Factory>
{
  Isolate *const isolate_;
  const CodeDesc &code_desc_;
  const Code::Kind kind_;

  MaybeHandle<Object> self_reference_;
  int32_t builtin_index_ = Builtins::kNoBuiltinId;
  int32_t kind_specific_flags_ = 0;
  Handle<ByteArray> source_position_table_;
  Handle<DeoptimizationData> deoptimization_data_ =
      DeoptimizationData::Empty(isolate_);
  bool is_executable_ = true;
  bool read_only_data_container_ = false;
  bool is_movable_ = true;
  bool is_turbofanned_ = false;
  int stack_slots_ = 0;
};

class UnionBytes
{
private:
  const uint8_t *one_bytes_;
  const uint16_t *two_bytes_;
  size_t length_;
};
class NativeModuleLoader
{
  struct ModuleCategories
  {
    bool is_initialized = false;
    std::set<std::string> can_be_required;
    std::set<std::string> cannot_be_required;
  };
  static NativeModuleLoader instance_;
  ModuleCategories module_categories_;
  NativeModuleRecordMap source_;
  NativeModuleCacheMap code_cache_;
  UnionBytes config_;

  // Used to synchronize access to the code cache map
  Mutex code_cache_mutex_;
};
template <typename T>
class Local
{
  T *val_;
};
template <typename T>
class MaybeLocal
{
private:
  T *val_;
};

template <class T>
using Handle = Local<T>;

class Context;
template <typename T>
class Maybe;
class Name;
class PropertyDescriptor;
class Utils;
class Data
{
};
class Value : public Data
{
};
class Object : public Value
{
  Maybe<bool> DefineProperty(
      Local<Context> context, Local<Name> key,
      PropertyDescriptor &descriptor);
};

//Maybe<bool> v8::Object::DefineProperty(v8::Local<v8::Context> context,v8::Local<Name> key,PropertyDescriptor &descriptor)
typedef uintptr_t Address;
class HandleBase
{
protected:
  Address *location_;
};
//当不希望某个类被继承，或不希望某个虚函数被重写，可以在类名和虚函数后添加final关键字
template <typename T>
class Handle final : public HandleBase
{
  class ObjectRef
  {
  private:
    T object_;
  };
};
namespace internal
{
  class Isolate;
  typedef uintptr_t Address;
} // namespace internal

class HandleScope
{
  internal::Isolate *isolate_;
  internal::Address *prev_next_;
  internal::Address *prev_limit_;
};
class HiddenFactory;
class Isolate final : private HiddenFactory
{
};