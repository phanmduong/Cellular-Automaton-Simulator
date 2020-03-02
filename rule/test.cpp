 #include <iostream>
#include <dlfcn.h>
#include "../rule.h"
#include <vector>



int main() {
    void* handle = dlopen("./rule.so", RTLD_LAZY);
    typedef void (*rule_t)();
    typedef vector<Rule*> (*rule_t2)();
    dlerror();
    rule_t initRules = (rule_t) dlsym(handle, "initRules");
    initRules();
    rule_t2 getAllRules = (rule_t2) dlsym(handle, "getAllRules");
    vector<Rule*> rules = getAllRules();
    for(unsigned int i = 0; i < rules.size(); i++)
    cout << rules[i]->getName() << "\n";
    dlclose(handle);
}
