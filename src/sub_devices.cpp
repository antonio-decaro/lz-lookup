#include <level_zero/ze_api.h>
#include "utils.hpp"
#include <vector>
#include <iostream>
#include <ctime>


void printDeviceProperties(ze_device_handle_t device, std::string tab);
void printDriverProperties(ze_driver_handle_t driver);

std::vector<ze_driver_handle_t> getAllDrivers() {
    
    std::vector<ze_driver_handle_t> allDrivers;
    uint32_t driverCount = 0;
    checkErrors(zeDriverGet(&driverCount, nullptr));

    allDrivers.resize(driverCount);
    checkErrors(zeDriverGet(&driverCount, allDrivers.data()));

    return allDrivers;
}

std::vector<ze_device_handle_t> getAllDevices(ze_driver_handle_t hDriver) {
    std::vector<ze_device_handle_t> allDevices;

    uint32_t deviceCount = 0;
    checkErrors(zeDeviceGet(hDriver, &deviceCount, nullptr));

    allDevices.resize(deviceCount);
    checkErrors(zeDeviceGet(hDriver, &deviceCount, allDevices.data()));

    return allDevices;
}

std::string typeToString(ze_device_type_t type) {
    switch (type)
    {
    case ZE_DEVICE_TYPE_GPU:
        return "GPU";
    case ZE_DEVICE_TYPE_CPU:
        return "CPU";
    case ZE_DEVICE_TYPE_FPGA:
        return "FPGA";
    case ZE_DEVICE_TYPE_MCA:
        return "MCA";
    case ZE_DEVICE_TYPE_VPU:
        return "VPU";
    case ZE_DEVICE_TYPE_FORCE_UINT32:
        return "FORCE_UINT32";
    default:
        return "Unknown";
    }
}

void printDeviceGeneralInfo(ze_device_handle_t device, std::string tab) {
    ze_device_properties_t props {};
    props.stype = ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES;

    if (checkErrors(zeDeviceGetProperties(device, &props))) {
        std::cout << tab << "Error getting device general properties" << std::endl;
        return;
    }

    std::cout << tab << "- Name: " << props.name << std::endl;
    std::cout << tab << "- Type: " << typeToString(props.type) << std::endl;
    std::cout << tab << "- Vendor ID: " << props.vendorId << std::endl;
    std::cout << tab << "- Device ID: " << props.deviceId << std::endl;
    std::cout << tab << "- Num Slices: " << props.numSlices << std::endl;
    std::cout << tab << "- Num Subslices per Slice: " << props.numSubslicesPerSlice << std::endl;
    std::cout << tab << "- Num EU per Subslice: " << props.numEUsPerSubslice << std::endl;
    std::cout << tab << "- Num Threads per EU: " << props.numThreadsPerEU << std::endl;
    std::cout << tab << "- Physical EU SIMD Width: " << props.physicalEUSimdWidth << std::endl;
    std::cout << tab << "- Command Queue Priority: " << props.maxCommandQueuePriority << std::endl;
    std::cout << tab << "- Max Hardware Contexts: " << props.maxHardwareContexts << std::endl;
    std::cout << tab << "- Max Memory Allocation Size: " << props.maxMemAllocSize << std::endl;
}

void printDeviceComputProperties(ze_device_handle_t device, std::string tab) {
    
    ze_device_compute_properties_t props {};
    props.stype = ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES;

    if (checkErrors(zeDeviceGetComputeProperties(device, &props))) {
        std::cout << tab << "Error getting device compute properties" << std::endl;
        return;
    }

    std::cout << tab << "- Max Group Count X: " << props.maxGroupCountX << std::endl;
    std::cout << tab << "- Max Group Count Y: " << props.maxGroupCountY << std::endl;
    std::cout << tab << "- Max Group Count Z: " << props.maxGroupCountZ << std::endl;

    std::cout << tab << "- Max Group Size X: " << props.maxGroupSizeX << std::endl;
    std::cout << tab << "- Max Group Size Y: " << props.maxGroupSizeY << std::endl;
    std::cout << tab << "- Max Group Size Z: " << props.maxGroupSizeZ << std::endl;

    std::cout << tab << "- Max Total Group Size: " << props.maxTotalGroupSize << std::endl;
    std::cout << tab << "- Max Shared Local Memory: " << props.maxSharedLocalMemory << std::endl;
    std::cout << tab << "- Num Sub Group Sizes: " << props.numSubGroupSizes << std::endl;
    std::cout << tab << "- Sub Group Sizes: ";
    for (int i = 0; i < props.numSubGroupSizes; ++i) {
        std::cout << props.subGroupSizes[i] << " ";
    }
    std::cout << std::endl;
}

void printDeviceMemoryProperty(ze_device_memory_properties_t props, std::string tab) {
    std::cout << tab << "- Name: " << props.name << std::endl;
    std::cout << tab << "- Total Size: " << props.totalSize << std::endl;
    std::cout << tab << "- Max Bus Width: " << props.maxBusWidth << std::endl;
    std::cout << tab << "- Max Clock Rate: " << props.maxClockRate << std::endl;
}

void printDeviceCacheProperties(ze_device_cache_properties_t props, std::string tab) {
    std::cout << tab << "- Cache Size: " << props.cacheSize << std::endl;
    std::string can_control = "NO";
    if (props.flags & ZE_DEVICE_CACHE_PROPERTY_FLAG_USER_CONTROL) {
        can_control = "YES";
    }
    std::cout << tab << "- User Control: " << can_control << std::endl;
}

std::string accessPropToString(ze_memory_access_cap_flags_t access) {
    std::string res = "";
    if (access & ZE_MEMORY_ACCESS_CAP_FLAG_RW) {
        res += "RW ";
    }
    if (access & ZE_MEMORY_ACCESS_CAP_FLAG_ATOMIC) {
        res += "ATOMIC ";
    }
    if (access & ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT) {
        res += "CONCURRENT ";
    }
    if (access & ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC) {
        res += "CONCURRENT_ATOMIC ";
    }
    return res == "" ? "NONE" : res;
}

std::string externMemPropToString(ze_external_memory_type_flags_t type) {
    std::string res = "";
    if (type & ZE_EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_FD) {
        res += "OPAQUE_FD ";
    }
    if (type & ZE_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF) {
        res += "DMA_BUF ";
    }
    if (type & ZE_EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_WIN32) {
        res += "OPAQUE_WIN32 ";
    }
    if (type & ZE_EXTERNAL_MEMORY_TYPE_FLAG_D3D11_TEXTURE) {
        res += "D3D11_TEXTURE ";
    }
    if (type & ZE_EXTERNAL_MEMORY_TYPE_FLAG_D3D11_TEXTURE_KMT) {
        res += "D3D11_TEXTURE_KMT ";
    }
    if (type & ZE_EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_WIN32_KMT) {
        res += "OPAQUE_WIN32_KMT ";
    }
    if (type & ZE_EXTERNAL_MEMORY_TYPE_FLAG_D3D12_HEAP) {
        res += "D3D12_HEAP ";
    }
    if (type & ZE_EXTERNAL_MEMORY_TYPE_FLAG_D3D12_RESOURCE) {
        res += "D3D12_RESOURCE ";
    }
    return res == "" ? "NONE" : res;
}

void printMemoryAccessProperties(ze_device_memory_access_properties_t props, std::string tab) {
    
    std::cout << tab << "- Host Alloc Capabilities: " << accessPropToString(props.hostAllocCapabilities) << std::endl;
    std::cout << tab << "- Device Alloc Capabilities: " << accessPropToString(props.deviceAllocCapabilities) << std::endl;
    std::cout << tab << "- Shared Single Device Alloc Capabilities: " << accessPropToString(props.sharedSingleDeviceAllocCapabilities) << std::endl;
    std::cout << tab << "- Shared Cross Device Alloc Capabilities: " << accessPropToString(props.sharedCrossDeviceAllocCapabilities) << std::endl;
    std::cout << tab << "- Shared System Alloc Capabilities: " << accessPropToString(props.sharedSystemAllocCapabilities) << std::endl;
}

void printExternalMemoryProperties(ze_device_external_memory_properties_t props, std::string tab) {
    std::cout << tab << "- Supported external memory import types for memory allocations: " << accessPropToString(props.imageImportTypes) << std::endl;
    std::cout << tab << "- Supported external memory export types for memory allocations: " << accessPropToString(props.imageExportTypes) << std::endl;
    std::cout << tab << "- Supported external memory import types for images: " << accessPropToString(props.imageImportTypes) << std::endl;
    std::cout << tab << "- Supported external memory export types for images: " << accessPropToString(props.imageExportTypes) << std::endl;
}

void printDeviceMemoryProperties(ze_device_handle_t device, std::string tab) {

    ze_device_memory_access_properties_t memacc_prop;
    ze_device_external_memory_properties_t extmem_prop;
    std::vector<ze_device_memory_properties_t> mem_props;
    std::vector<ze_device_cache_properties_t> cache_props;
    uint32_t props_count = 0;

    memacc_prop.stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES;
    if (checkErrors(zeDeviceGetMemoryAccessProperties(device, &memacc_prop))) {
        std::cout << tab << "Error getting device memory access properties" << std::endl;
        return;
    }
    printMemoryAccessProperties(memacc_prop, tab);

    extmem_prop.stype = ZE_STRUCTURE_TYPE_DEVICE_EXTERNAL_MEMORY_PROPERTIES;
    if (checkErrors(zeDeviceGetExternalMemoryProperties(device, &extmem_prop))) {
        std::cout << tab << "Error getting device external memory properties" << std::endl;
        return;
    }
    printExternalMemoryProperties(extmem_prop, tab);

    checkErrors(zeDeviceGetMemoryProperties(device, &props_count, nullptr));
    mem_props.resize(props_count);
    if (checkErrors(zeDeviceGetMemoryProperties(device, &props_count, mem_props.data()))) {
        std::cout << tab << "Error getting device memory properties" << std::endl;
        return;
    }
    for (int i = 0; i < props_count; ++i) {
        std::cout << tab << "\t[MEMORY #" << i << "]" << std::endl;
        printDeviceMemoryProperty(mem_props[i], tab + "\t");
    }

    props_count = 0;
    checkErrors(zeDeviceGetCacheProperties(device, &props_count, nullptr));
    cache_props.resize(props_count);
    if (checkErrors(zeDeviceGetCacheProperties(device, &props_count, cache_props.data()))) {
        std::cout << tab << "Error getting device memory access properties" << std::endl;
        return;
    }
    for (int i = 0; i < props_count; ++i) {
        std::cout << tab << "\t[CACHE #" << i << "]" << std::endl;
        printDeviceCacheProperties(cache_props[i], tab + "\t");
    }
}

void printSubDeviceProperties(ze_device_handle_t device, std::string tab) {
    uint32_t subDeviceCount = 0;
    std::vector<ze_device_handle_t> subDevices;

    if (checkErrors(zeDeviceGetSubDevices(device, &subDeviceCount, nullptr))) {
        std::cout << tab << "Error getting device sub-devices properties" << std::endl;
        return;
    }

    subDevices.resize(subDeviceCount);
    if (checkErrors(zeDeviceGetSubDevices(device, &subDeviceCount, subDevices.data()))) {
        std::cout << tab << "Error getting device sub-devices properties" << std::endl;
        return;
    }

    std::cout << tab << "- Sub-Device Count: " << subDeviceCount << std::endl;
    for (int i = 0; i < subDeviceCount; ++i) {
        std::cout << tab << "\t[SUB-DEVICE #" << i << "]" << std::endl;
        printDeviceProperties(subDevices[i], tab + "\t");
    }
}

void printDeviceImageProperties(ze_device_handle_t device, std::string tab) {
    ze_device_image_properties_t props {};
    props.stype = ZE_STRUCTURE_TYPE_DEVICE_IMAGE_PROPERTIES;

    if (checkErrors(zeDeviceGetImageProperties(device, &props))) {
        std::cout << tab << "Error getting device image properties" << std::endl;
        return;
    }

    std::cout << tab << "- Max Image 1D Width: " << props.maxImageDims1D << std::endl;
    std::cout << tab << "- Max Image 2D Width: " << props.maxImageDims2D << std::endl;
    std::cout << tab << "- Max Image 3D Width: " << props.maxImageDims3D << std::endl;
    std::cout << tab << "- Max Image Array Slices: " << props.maxImageArraySlices << std::endl;
    std::cout << tab << "- Max Samplers: " << props.maxSamplers << std::endl;
    std::cout << tab << "- Max Read Image Args: " << props.maxReadImageArgs << std::endl;
    std::cout << tab << "- Max Write Image Args: " << props.maxWriteImageArgs << std::endl;
}

void printDeviceProperties(ze_device_handle_t device, std::string tab) {
    std::cout << tab << "[General Info]" << std::endl;
    printDeviceGeneralInfo(device, tab);

    std::cout << tab << "[Compute Properties]" << std::endl;
    printDeviceComputProperties(device, tab);

    std::cout << tab << "[Memory Properties]" << std::endl;
    printDeviceMemoryProperties(device, tab);

    std::cout << tab << "[Image Properties]" << std::endl;
    printDeviceImageProperties(device, tab);

    std::cout << tab << "[Sub-Devices Properties]" << std::endl;
    printSubDeviceProperties(device, tab);
}

void printDriverProperties(ze_driver_handle_t driver) {
    ze_driver_properties_t dProps {};
    dProps.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;

    if (!checkErrors(zeDriverGetProperties(driver, &dProps))) {
        std::cout << "Driver Version: " << dProps.driverVersion << std::endl;
    } else {
        std::cout << "Error getting driver properties" << std::endl;
    }
}

int main() {

    // Initialize the driver
    ze_result_t res = zeInit(0);
    if (checkErrors(res)) {
        exit(1);
    }

    // Discover all the driver instances
    auto all_drivers = getAllDrivers();

    int num_dev = 0;
    for (auto driver : all_drivers) {
        std::cout << "********** [DRIVER] **********" << std::endl;
        printDriverProperties(driver);
        auto allDevices = getAllDevices(driver);
        for (auto device : allDevices) {
            std::cout << "[DEVICE #" << num_dev++ << "]" << std::endl;
            printDeviceProperties(device, "\t");
        }
    }
}