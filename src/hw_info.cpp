#include <level_zero/zes_api.h>
#include "utils.hpp"
#include <iostream>
#include <vector>

std::vector<zes_driver_handle_t> getAllDrivers() {
    uint32_t numDrivers = 0;
    std::vector<zes_driver_handle_t> allDrivers;
    ze_result_t res = zesDriverGet(&numDrivers, nullptr);
    if (checkErrors(res)) {
        exit(1);
    }
    
    allDrivers.resize(numDrivers);
    res = zesDriverGet(&numDrivers, allDrivers.data());
    if (checkErrors(res)) {
        exit(1);
    }

    return allDrivers;
}

std::vector<zes_device_handle_t> getAllDevices(zes_driver_handle_t driver) {
    uint32_t num_devices = 0;
    std::vector<zes_device_handle_t> all_devices;

    if (checkErrors(zesDeviceGet(driver, &num_devices, nullptr))){
        exit(1);
    }
    all_devices.resize(num_devices);
    if (checkErrors(zesDeviceGet(driver, &num_devices, all_devices.data()))){
        exit(1);
    }

    return all_devices;
}

void printDeviceGeneralInfo(zes_device_handle_t device, std::string tab) {
    zes_device_properties_t prop {};
    prop.stype = ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES;

    if (checkErrors(zesDeviceGetProperties(device, &prop))) {
        std::cerr << "Failed to get device properties" << std::endl;
    }
    
    std::cout << tab << "- Model Name: " << prop.modelName << std::endl;
    std::cout << tab << "- Vendor Name: " << prop.vendorName << std::endl;
    std::cout << tab << "- Brand Name: " << prop.brandName << std::endl;
    std::cout << tab << "- Board Number: " << prop.boardNumber << std::endl;
    std::cout << tab << "- Serial Number: " << prop.serialNumber << std::endl;
    std::cout << tab << "- Num Sub-Devices: " << prop.numSubdevices << std::endl;
    std::cout << tab << "- Device Driver Version: " << prop.driverVersion << std::endl;
}

void printFrequencyDomainInfo(zes_freq_handle_t freq_domain, std::string tab) {
    zes_freq_properties_t prop {};
    prop.stype = ZES_STRUCTURE_TYPE_FREQ_PROPERTIES;

    if (checkErrors(zesFrequencyGetProperties(freq_domain, &prop))) {
        std::cerr << "Failed to get frequency properties" << std::endl;
        return;
    }

    std::string type;
    switch (prop.type) {
        case ZES_FREQ_DOMAIN_GPU:
            type = "CORE";
            break;
        case ZES_FREQ_DOMAIN_MEMORY:
            type = "MEMORY";
            break;
        case ZES_FREQ_DOMAIN_MEDIA:
            type = "MEDIA";
            break;
        default:
            type = "UNKNOWN";
    }

    std::cout << tab << "- Type: " << type << std::endl;
    std::cout << tab << "- Can Control: " << prop.canControl << std::endl;
    std::cout << tab << "- Is Throttle Event Supported: " << BOOL(prop.isThrottleEventSupported) << std::endl;
    std::cout << tab << "- Min: " << prop.min << std::endl;
    std::cout << tab << "- Max: " << prop.max << std::endl;
    std::cout << tab << "- On Subdevice: " << BOOL(prop.onSubdevice) << std::endl;
    std::cout << tab << "- Subdevice ID: " << prop.subdeviceId << std::endl;
}

void printDeviceFrequencyInfo(zes_device_handle_t device, std::string tab) {
    uint32_t num_freq_domains = 0;
    std::vector<zes_freq_handle_t> all_freq_domains;

    checkErrors(zesDeviceEnumFrequencyDomains(device, &num_freq_domains, nullptr));
    all_freq_domains.resize(num_freq_domains);
    if (checkErrors(zesDeviceEnumFrequencyDomains(device, &num_freq_domains, all_freq_domains.data()))) {
        std::cerr << "Failed to get frequency domains" << std::endl;
        return;
    }

    std::cout << tab << "- Number of Frequency Domains: " << num_freq_domains << std::endl;
    for (int i = 0; i < all_freq_domains.size(); i++) {
        std::cout << tab << "\t[FREQUENCY DOMAIN #" << i << "]" << std::endl;
        printFrequencyDomainInfo(all_freq_domains[i], tab + "\t");
    }
}

void printPowerDomainInfo(zes_pwr_handle_t handle, std::string tab) {
    zes_power_properties_t prop {};
    prop.stype = ZES_STRUCTURE_TYPE_POWER_PROPERTIES;

    if (checkErrors(zesPowerGetProperties(handle, &prop))) {
        std::cerr << "Failed to get power properties" << std::endl;
        return;
    }

    std::string domain_type = "UNKNOWN";
    if (prop.pNext != nullptr) {
        zes_power_ext_properties_t* ext_prop = reinterpret_cast<zes_power_ext_properties_t*>(prop.pNext);
        switch (ext_prop->domain) {
            case ZES_POWER_DOMAIN_CARD:
                domain_type = "CARD";
                break;
            case ZES_POWER_DOMAIN_PACKAGE:
                domain_type = "PACKAGE";
                break;
            case ZES_POWER_DOMAIN_FORCE_UINT32:
                domain_type = "FORCE_UINT32";
                break;
            case ZES_POWER_DOMAIN_UNKNOWN:
            default:
                domain_type = "UNKNOWN";
        }
    }

    std::cout << tab << "- Domain Type: " << domain_type << std::endl;
    std::cout << tab << "- Can Control: " << prop.canControl << std::endl;
    std::cout << tab << "- Default Limit: " << prop.defaultLimit << std::endl;
    std::cout << tab << "- Max Limit: " << prop.maxLimit << std::endl;
    std::cout << tab << "- Min Limit: " << prop.minLimit << std::endl;
    std::cout << tab << "- On Subdevice: " << BOOL(prop.onSubdevice) << std::endl;
    std::cout << tab << "- Subdevice ID: " << prop.subdeviceId << std::endl;
}

void printDevicePowerInfo(zes_device_handle_t device, std::string tab) {
    uint32_t num_power_domains = 0;
    std::vector<zes_pwr_handle_t> all_power_domains;
    checkErrors(zesDeviceEnumPowerDomains(device, &num_power_domains, nullptr));
    all_power_domains.resize(num_power_domains);
    if (checkErrors(zesDeviceEnumPowerDomains(device, &num_power_domains, all_power_domains.data()))) {
        std::cerr << "Failed to get power domains" << std::endl;
        return;
    }

    std::cout << tab << "- Number of Power Domains: " << num_power_domains << std::endl;
    for (int i = 0; i < all_power_domains.size(); i++) {
        std::cout << tab << "\t[POWER DOMAIN #" << i << "]" << std::endl;
        printPowerDomainInfo(all_power_domains[i], tab + "\t");
    }
}

void printPsuInfo(zes_psu_handle_t handle, std::string tab) {
    zes_psu_properties_t prop {};
    prop.stype = ZES_STRUCTURE_TYPE_PSU_PROPERTIES;

    if (checkErrors(zesPsuGetProperties(handle, &prop))) {
        std::cerr << "Failed to get PSU properties" << std::endl;
        return;
    }

    std::cout << tab << "- Max Electrical Current (ma): " << prop.ampLimit << std::endl;
    std::cout << tab << "- Has Fan: " << BOOL(prop.haveFan) << std::endl;
    std::cout << tab << "- On Subdevice: " << BOOL(prop.onSubdevice) << std::endl;
}

void printPsusProperties(zes_device_handle_t device, std::string tab) {
    uint32_t num_psus = 0;
    std::vector<zes_psu_handle_t> all_psus;

    checkErrors(zesDeviceEnumPsus(device, &num_psus, nullptr));
    all_psus.resize(num_psus);
    if (checkErrors(zesDeviceEnumPsus(device, &num_psus, all_psus.data()))) {
        std::cerr << "Failed to get PSU domains" << std::endl;
        return;
    }

    std::cout << tab << "- Number of PSU Domains: " << num_psus << std::endl;
    for (int i = 0; i < all_psus.size(); i++) {
        std::cout << tab << "\t[PSU #" << i << "]" << std::endl;
        printPsuInfo(all_psus[i], tab + "\t");
    }
}

void printTempInfo(zes_temp_handle_t temp, std::string tab) {
    zes_temp_properties_t prop {};
    prop.stype = ZES_STRUCTURE_TYPE_TEMP_PROPERTIES;

    if (checkErrors(zesTemperatureGetProperties(temp, &prop))) {
        std::cerr << "Failed to get temperature properties" << std::endl;
        return;
    }

    std::cout << tab << "- Max Temperature: " << prop.maxTemperature << std::endl;
    std::cout << tab << "- Is Critical Temp Supported: " << BOOL(prop.isCriticalTempSupported) << std::endl;
    std::cout << tab << "- Is Threshold1 Supported: " << BOOL(prop.isThreshold1Supported) << std::endl;
    std::cout << tab << "- Is Threshold2 Supported: " << BOOL(prop.isThreshold2Supported) << std::endl;
    std::cout << tab << "- On Subdevice: " << BOOL(prop.onSubdevice) << std::endl;
    std::cout << tab << "- Subdevice ID: " << prop.subdeviceId << std::endl;
}

void printTempProperties(zes_device_handle_t device, std::string tab) {
    uint32_t num_temp_sensors = 0;
    std::vector<zes_temp_handle_t> all_temp_sensors;

    checkErrors(zesDeviceEnumTemperatureSensors(device, &num_temp_sensors, nullptr));
    all_temp_sensors.resize(num_temp_sensors);
    if (checkErrors(zesDeviceEnumTemperatureSensors(device, &num_temp_sensors, all_temp_sensors.data()))) {
        std::cerr << "Failed to get temperature sensors" << std::endl;
        return;
    }
    
    std::cout << tab << "- Number of Temperature Sensors: " << num_temp_sensors << std::endl;
    for (int i = 0; i < all_temp_sensors.size(); i++) {
        std::cout << tab << "\t[TEMPERATURE SENSOR #" << i << "]" << std::endl;
        printTempInfo(all_temp_sensors[i], tab + "\t");
    }
}

void printDeviceProperties(zes_device_handle_t device, std::string tab) {
    std::cout << tab << "[General Info]" << std::endl;
    printDeviceGeneralInfo(device, tab);

    std::cout << tab << "[Frequency Info]" << std::endl;
    printDeviceFrequencyInfo(device, tab);

    std::cout << tab << "[Power Info]" << std::endl;
    printDevicePowerInfo(device, tab);

    std::cout << tab << "[PSU Info]" << std::endl;
    printPsusProperties(device, tab);

    // std::cout << tab << "[Temperature Info]" << std::endl;
    // printTempProperties(device, tab);
}

int main() {
    // Initialize the driver
    ze_result_t res = zesInit(0);
    if (checkErrors(res)) {
        exit(1);
    }

    // Discover all the driver instances
    auto all_drivers = getAllDrivers();

    int num_dev = 0;
    for (auto driver : all_drivers) {
        std::cout << "********** [DRIVER] **********" << std::endl;
        auto allDevices = getAllDevices(driver);
        for (auto device : allDevices) {
            std::cout << "[DEVICE #" << num_dev++ << "]" << std::endl;
            printDeviceProperties(device, "\t");
        }
    }
}