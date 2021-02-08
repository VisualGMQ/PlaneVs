#ifndef MANAGER_HPP
#define MANAGER_HPP
#include <vector>
#include <type_traits>
#include <typeinfo>

#include "base/id.hpp"
#include "base/log.hpp"
using std::vector;

/* TODO make manager can recongnize MANAGED_TYPE by follow code
template <typename MANAGED_TYPE,
          std::enable_if_t<
              std::is_base_of<HasID, MANAGED_TYPE>::value, int
          > = 0>
*/

template <typename MANAGED_TYPE>
class IdInstanceManager {
 public:
     static MANAGED_TYPE* CreatePreset(PresetResourcesId id) {
         return create(id);
     }

     static MANAGED_TYPE* Create(IdType id) {
         return create(id);
     }

     static void FreeById(IdType id) {
         for (auto it = _instances.begin(); it != _instances.end(); it++) {
             if ((*it)->GetId() == id) {
                 delete *it;
                 _instances.erase(it);
                 return;
             }
         }
     }

     static MANAGED_TYPE* GetById(IdType id) {
         for (MANAGED_TYPE* buf : _instances) {
             if (buf->GetId() == id)
                 return buf;
         }
         Logw("Manager::GetById", "you required a non-exist id %u", id);
         return nullptr;
     }

     static void Destroy() {
         for (MANAGED_TYPE* buf : _instances)
             delete buf;
         _instances.clear();
     }

 private:
     static vector<MANAGED_TYPE*> _instances;

     static MANAGED_TYPE* create(IdType id) {
         MANAGED_TYPE* buf = new MANAGED_TYPE(id);
         _instances.push_back(buf);
         return buf;
     }
};

template <typename TYPE>
vector<TYPE*> IdInstanceManager<TYPE>::_instances;

#endif

