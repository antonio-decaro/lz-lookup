#pragma once

#include <level_zero/ze_api.h>
#include <iostream>

#define BOOL(x) (x ? "TRUE" : "FALSE")

bool checkErrors(ze_result_t res) {
  switch (res) {
    case ZE_RESULT_SUCCESS:
      return false;
    case ZE_RESULT_NOT_READY:
      std::cerr << "ZE_RESULT_NOT_READY" << std::endl;
      break;
    case ZE_RESULT_ERROR_DEVICE_LOST:
      std::cerr << "ZE_RESULT_ERROR_DEVICE_LOST" << std::endl;
      break;
    case ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY:
      std::cerr << "ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY" << std::endl;
      break;
    case ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY:
      std::cerr << "ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY" << std::endl;
      break;
    case ZE_RESULT_ERROR_MODULE_BUILD_FAILURE:
      std::cerr << "ZE_RESULT_ERROR_MODULE_BUILD_FAILURE" << std::endl;
      break;
    case ZE_RESULT_ERROR_MODULE_LINK_FAILURE:
      std::cerr << "ZE_RESULT_ERROR_MODULE_LINK_FAILURE" << std::endl;
      break;
    case ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET:
      std::cerr << "ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET" << std::endl;
      break;
    case ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE:
      std::cerr << "ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE" << std::endl;
      break;
    case ZE_RESULT_EXP_ERROR_DEVICE_IS_NOT_VERTEX:
      std::cerr << "ZE_RESULT_EXP_ERROR_DEVICE_IS_NOT_VERTEX" << std::endl;
      break;
    case ZE_RESULT_EXP_ERROR_VERTEX_IS_NOT_DEVICE:
      std::cerr << "ZE_RESULT_EXP_ERROR_VERTEX_IS_NOT_DEVICE" << std::endl;
      break;
    case ZE_RESULT_EXP_ERROR_REMOTE_DEVICE:
      std::cerr << "ZE_RESULT_EXP_ERROR_REMOTE_DEVICE" << std::endl;
      break;
    case ZE_RESULT_EXP_ERROR_OPERANDS_INCOMPATIBLE:
      std::cerr << "ZE_RESULT_EXP_ERROR_OPERANDS_INCOMPATIBLE" << std::endl;
      break;
    case ZE_RESULT_EXP_RTAS_BUILD_RETRY:
      std::cerr << "ZE_RESULT_EXP_RTAS_BUILD_RETRY" << std::endl;
      break;
    case ZE_RESULT_EXP_RTAS_BUILD_DEFERRED:
      std::cerr << "ZE_RESULT_EXP_RTAS_BUILD_DEFERRED" << std::endl;
      break;
    case ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS:
      std::cerr << "ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS" << std::endl;
      break;
    case ZE_RESULT_ERROR_NOT_AVAILABLE:
      std::cerr << "ZE_RESULT_ERROR_NOT_AVAILABLE" << std::endl;
      break;
    case ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE:
      std::cerr << "ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE" << std::endl;
      break;
    case ZE_RESULT_WARNING_DROPPED_DATA:
      std::cerr << "ZE_RESULT_WARNING_DROPPED_DATA" << std::endl;
      break;
    case ZE_RESULT_ERROR_UNINITIALIZED:
      std::cerr << "ZE_RESULT_ERROR_UNINITIALIZED" << std::endl;
      break;
    case ZE_RESULT_ERROR_UNSUPPORTED_VERSION:
      std::cerr << "ZE_RESULT_ERROR_UNSUPPORTED_VERSION" << std::endl;
      break;
    case ZE_RESULT_ERROR_UNSUPPORTED_FEATURE:
      std::cerr << "ZE_RESULT_ERROR_UNSUPPORTED_FEATURE" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_ARGUMENT:
      std::cerr << "ZE_RESULT_ERROR_INVALID_ARGUMENT" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_NULL_HANDLE:
      std::cerr << "ZE_RESULT_ERROR_INVALID_NULL_HANDLE" << std::endl;
      break;
    case ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE:
      std::cerr << "ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_NULL_POINTER:
      std::cerr << "ZE_RESULT_ERROR_INVALID_NULL_POINTER" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_SIZE:
      std::cerr << "ZE_RESULT_ERROR_INVALID_SIZE" << std::endl;
      break;
    case ZE_RESULT_ERROR_UNSUPPORTED_SIZE:
      std::cerr << "ZE_RESULT_ERROR_UNSUPPORTED_SIZE" << std::endl;
      break;
    case ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT:
      std::cerr << "ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT:
      std::cerr << "ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_ENUMERATION:
      std::cerr << "ZE_RESULT_ERROR_INVALID_ENUMERATION" << std::endl;
      break;
    case ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION:
      std::cerr << "ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION" << std::endl;
      break;
    case ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT:
      std::cerr << "ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_NATIVE_BINARY:
      std::cerr << "ZE_RESULT_ERROR_INVALID_NATIVE_BINARY" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_GLOBAL_NAME:
      std::cerr << "ZE_RESULT_ERROR_INVALID_GLOBAL_NAME" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_KERNEL_NAME:
      std::cerr << "ZE_RESULT_ERROR_INVALID_KERNEL_NAME" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_FUNCTION_NAME:
      std::cerr << "ZE_RESULT_ERROR_INVALID_FUNCTION_NAME" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION:
      std::cerr << "ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION:
      std::cerr << "ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX:
      std::cerr << "ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE:
      std::cerr << "ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE:
      std::cerr << "ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED:
      std::cerr << "ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED" << std::endl;
      break;
    case ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE:
      std::cerr << "ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE" << std::endl;
      break;
    case ZE_RESULT_ERROR_OVERLAPPING_REGIONS:
      std::cerr << "ZE_RESULT_ERROR_OVERLAPPING_REGIONS" << std::endl;
      break;
    case ZE_RESULT_WARNING_ACTION_REQUIRED:
      std::cerr << "ZE_RESULT_WARNING_ACTION_REQUIRED" << std::endl;
      break;
    case ZE_RESULT_ERROR_UNKNOWN:
      std::cerr << "ZE_RESULT_ERROR_UNKNOWN" << std::endl;
      break;
    case ZE_RESULT_FORCE_UINT32:
      std::cerr << "ZE_RESULT_FORCE_UINT32" << std::endl;
      break;
    default:
      std::cerr << "Unknown error" << std::endl;
      break;
  }  
  return true;
}