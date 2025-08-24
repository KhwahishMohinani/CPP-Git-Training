#include <iostream>
#include <dlfcn.h>

int main()
{
    void *core = dlopen("./libcore.so", RTLD_LAZY | RTLD_GLOBAL);
    if (!core)
    {
        std::cout << "Cannot load core file " << dlerror() << "\n";
        dlclose(core);
        return 1;
    }
    void *plugin = dlopen("./libplugin.so", RTLD_LAZY | RTLD_LOCAL);
    if (!plugin)
    {
        std::cerr << "Cannot load plugin file " << dlerror() << '\n';
        dlclose(plugin);
        return 1;
    }

    void (*pluginFunc)(void) = (void (*)(void))dlsym(plugin, "printPlugin");
    const char *error = dlerror();
    if (error)
    {
        std::cerr << "Cannot load printPlugin symbol " << error << '\n';
        return 1;
    }
    pluginFunc();
    dlclose(plugin);
    dlclose(core);
    return 0;
}