
#define __CL_ENABLE_EXCEPTIONS

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#ifdef CL_VERSION_1_3
#undef CL_VERSION_1_3
#endif


#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include <iostream>
#include <memory>

using namespace cl;

int detectCPUs(unsigned int platform_idx)
{
    // declarations
    cl_int err;
    
    // subtract one for zero indexing
    unsigned int plat_idx = platform_idx - 1;
    
    // Get available platforms
    std::vector<Platform> platforms;
    Platform::get(&platforms);

    if(platforms.size() == 0){
        std::cerr << "No platforms found. Check OpenCL installation!\n" << std::endl;
    } 
        
    if (plat_idx > platforms.size()){
        std::cerr << "platform index greater than number of platforms." << std::endl;
    }

    // Select the platform and create a context using this platform
    cl_context_properties cps[3] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)(platforms[plat_idx])(),
        0
    };
    
    Context context = Context(CL_DEVICE_TYPE_CPU, cps, NULL, NULL, &err);

    // Get a list of devices on this platform
    std::vector<Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    
    return devices.size();
}
    
int main()
{
    std::cout << detectCPUs(1) << std::endl;
    return 0;
}


