#include <node_api.h>
#include "common.h"
#include "cpor.h"

/*ret: 0 - Cheating, 1 - Verified, -1 - error.*/
napi_value CporVerify(napi_env env, napi_callback_info info) {
    napi_value argv[6];
    size_t argc = 6;

    size_t temp = 0;

    int32_t ret = 0;
    napi_value ret_napi;
    napi_value ret_napi_error;
    
    uint32_t lambda = 0, block_size = 0;
    char *filename = 0;
    char *key_data = 0, *t_data = 0, *tag_data = 0;

    napi_create_int32(env, -1, &ret_napi_error);

    NAPI_CALL_BASE(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL), ret_napi_error);

    if(argc != 6) {
        napi_throw_error(env, "EINVAL", "Invalid number of arguments");
        return ret_napi_error;
    }

    // get the length of filename
    NAPI_CALL_BASE(env, napi_get_value_string_utf8(env, argv[0], NULL, 0, &temp), ret_napi_error);
    filename = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_utf8(env, argv[0], filename, temp + 1, &temp), ret_napi_error);

    // get the length of key_data
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], NULL, 0, &temp), ret_napi_error);
    key_data = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], key_data, temp + 1, &temp), ret_napi_error);

    // get the length of t_data
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], NULL, 0, &temp), ret_napi_error);
    t_data = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], t_data, temp + 1, &temp), ret_napi_error);
    
    // get the length of tag_data
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[3], NULL, 0, &temp), ret_napi_error);
    tag_data = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[3], tag_data, temp + 1, &temp), ret_napi_error);

    NAPI_CALL_BASE(env, napi_get_value_uint32(env, argv[4], &lambda), ret_napi_error);
    NAPI_CALL_BASE(env, napi_get_value_uint32(env, argv[5], &block_size), ret_napi_error);

    ret = cpor_verify(filename, key_data, t_data, tag_data, lambda, block_size);

    free(key_data); key_data = 0;
    free(t_data); t_data = 0;
    free(tag_data); tag_data = 0;

    NAPI_CALL_BASE(env, napi_create_int32(env, ret, &ret_napi), ret_napi_error);

    return ret_napi;
}

void Init(napi_env env, napi_value exports) {
    // napi_property_descriptor is to describe the exported attrs/methods.
    napi_property_descriptor desc = { "CporVerify", 0, CporVerify, 0, 0, 0, napi_default, 0 };
    // define exported method.
    NAPI_CALL_RETURN_VOID(env, napi_define_properties(env, exports, 1, &desc));
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
