#include <node_api.h>
#include "common.h"
#include "cpor.h"

#ifdef _WIN32
#include <windows.h>
static char *EncodingConvert(const char* strIn, int sourceCodepage, int targetCodepage)
{
	int unicodeLen = MultiByteToWideChar(sourceCodepage, 0, strIn, -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = (wchar_t *)malloc((unicodeLen + 1) * sizeof(wchar_t));
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(sourceCodepage, 0, strIn, -1, (LPWSTR)pUnicode, unicodeLen);
	char * pTargetData = NULL;
	int targetLen = WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, pTargetData, 0, NULL, NULL);
	pTargetData = (BYTE *)malloc((targetLen + 1) * sizeof(BYTE));
	memset(pTargetData, 0, targetLen + 1);
	WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, pTargetData, targetLen, NULL, NULL);
	free(pUnicode);
	return pTargetData;
}
#endif

napi_value CporChallenge(napi_env env, napi_callback_info info) {
    napi_value argv[3];
    size_t argc = 3;

    size_t temp = 0;

    char *challenge = 0;
    napi_value ret_napi;
    napi_value ret_napi_error;
    
    char *params = 0, *key_data = 0, *t_data = 0;

    napi_create_string_latin1(env, NULL, 0, &ret_napi_error);

    NAPI_CALL_BASE(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL), ret_napi_error);

    if(argc != 3) {
        napi_throw_error(env, "EINVAL", "Invalid number of arguments");
        return ret_napi_error;
    }

    // get the length of params
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[0], NULL, 0, &temp), ret_napi_error);
    params = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[0], params, temp + 1, &temp), ret_napi_error);

    // get the length of key_data
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], NULL, 0, &temp), ret_napi_error);
    key_data = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], key_data, temp + 1, &temp), ret_napi_error);

    // get the length of t_data
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], NULL, 0, &temp), ret_napi_error);
    t_data = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], t_data, temp + 1, &temp), ret_napi_error);

    challenge = (char *)cpor_challenge((CPOR_params *)params, key_data, t_data);

    free(params); params = NULL;
    free(key_data); key_data = NULL;
    free(t_data); t_data = NULL;

    NAPI_CALL_BASE(env, napi_create_string_latin1(env, challenge, sizeof(CPOR_challenge), &ret_napi), ret_napi_error);

    return ret_napi;
}

napi_value CporGetTags(napi_env env, napi_callback_info info) {
    napi_value argv[2];
    size_t argc = 2;

    size_t temp = 0;

    char *tags = 0;
    napi_value ret_napi;
    napi_value ret_napi_error;
    
    char *challenge = 0, *tag_data = 0;

    napi_create_string_latin1(env, NULL, 0, &ret_napi_error);

    NAPI_CALL_BASE(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL), ret_napi_error);

    if(argc != 2) {
        napi_throw_error(env, "EINVAL", "Invalid number of arguments");
        return ret_napi_error;
    }

    // get the length of challenge
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[0], NULL, 0, &temp), ret_napi_error);
    challenge = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[0], challenge, temp + 1, &temp), ret_napi_error);

    // get the length of tag_data
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], NULL, 0, &temp), ret_napi_error);
    tag_data = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], tag_data, temp + 1, &temp), ret_napi_error);

    tags = (char *)cpor_get_tags((CPOR_challenge *)challenge, tag_data);

    free(challenge); challenge = NULL;
    free(tag_data); tag_data = NULL;

    NAPI_CALL_BASE(env, napi_create_string_latin1(env, tags, sizeof(CPOR_tag *), &ret_napi), ret_napi_error);

    return ret_napi;
}

napi_value CporProveFile(napi_env env, napi_callback_info info) {
    napi_value argv[4];
    size_t argc = 4;

    size_t temp = 0;

    char *proof = 0;
    napi_value ret_napi;
    napi_value ret_napi_error;
    
    char *params = 0, *filename = 0, *challenge = 0;
    char *tags = 0;

    napi_create_string_latin1(env, NULL, 0, &ret_napi_error);

    NAPI_CALL_BASE(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL), ret_napi_error);

    if(argc != 4) {
        napi_throw_error(env, "EINVAL", "Invalid number of arguments");
        return ret_napi_error;
    }

    // get the length of params
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[0], NULL, 0, &temp), ret_napi_error);
    params = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[0], params, temp + 1, &temp), ret_napi_error);

    // get the length of filename
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], NULL, 0, &temp), ret_napi_error);
    filename = (char *)malloc((temp + 1) * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], filename, temp + 1, &temp), ret_napi_error);
    filename[temp] = '\0';

    // get the length of challenge
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], NULL, 0, &temp), ret_napi_error);
    challenge = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], challenge, temp + 1, &temp), ret_napi_error);

    // get the length of tags
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[3], NULL, 0, &temp), ret_napi_error);
    tags = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[3], tags, temp + 1, &temp), ret_napi_error);

    proof = (char *)cpor_prove_file((CPOR_params *)params, filename, (CPOR_challenge *)challenge, (CPOR_tag **)tags);

    free(params); params = NULL;
    free(filename); filename = NULL;
    free(challenge); challenge = NULL;
    free(tags); tags = NULL;

    NAPI_CALL_BASE(env, napi_create_string_latin1(env, proof, sizeof(CPOR_proof), &ret_napi), ret_napi_error);

    return ret_napi;
}

/*ret: 0 - Cheating, 1 - Verified, -1 - error.*/
napi_value CporVerifyFile(napi_env env, napi_callback_info info) {
    napi_value argv[6];
    size_t argc = 6;

    size_t temp = 0;

    int32_t success = 0;
    napi_value ret_napi;
    napi_value ret_napi_error;
    
    char *params = 0, *filename = 0, *key_data = 0, *t_data = 0, *challenge = 0, *proof = 0;

    napi_create_int32(env, -1, &ret_napi_error);

    NAPI_CALL_BASE(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL), ret_napi_error);

    if(argc != 6) {
        napi_throw_error(env, "EINVAL", "Invalid number of arguments");
        return ret_napi_error;
    }

    // get the length of params
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[0], NULL, 0, &temp), ret_napi_error);
    params = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[0], params, temp + 1, &temp), ret_napi_error);

    // get the length of filename
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], NULL, 0, &temp), ret_napi_error);
    filename = (char *)malloc((temp + 1) * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], filename, temp + 1, &temp), ret_napi_error);
    filename[temp] = '\0';

    // get the length of key_data
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], NULL, 0, &temp), ret_napi_error);
    key_data = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], key_data, temp + 1, &temp), ret_napi_error);

    // get the length of t_data
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[3], NULL, 0, &temp), ret_napi_error);
    t_data = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[3], t_data, temp + 1, &temp), ret_napi_error);

    // get the length of challenge
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[4], NULL, 0, &temp), ret_napi_error);
    challenge = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[4], challenge, temp + 1, &temp), ret_napi_error);

    // get the length of proof
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[5], NULL, 0, &temp), ret_napi_error);
    proof = (char *)malloc(temp * sizeof(char));
    NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[5], proof, temp + 1, &temp), ret_napi_error);

    success = cpor_verify_file((CPOR_params *)params, filename, key_data, t_data, (CPOR_challenge *)challenge, (CPOR_proof *)proof);

    free(params); params = NULL;
    free(filename); filename = NULL;
    free(key_data); key_data = NULL;
    free(t_data); t_data = NULL;
    free(challenge); challenge = NULL;
    free(proof); proof = NULL;

    NAPI_CALL_BASE(env, napi_create_int32(env, success, &ret_napi), ret_napi_error);

    return ret_napi;
}

// /*ret: 0 - Cheating, 1 - Verified, -1 - error.*/
// napi_value CporVerify(napi_env env, napi_callback_info info) {
//     napi_value argv[4];
//     size_t argc = 4;

//     size_t temp = 0;

//     int32_t ret = 0;
//     napi_value ret_napi;
//     napi_value ret_napi_error;
    
//     char *filename = 0;
//     char *key_data = 0, *t_data = 0, *tag_data = 0;

//     napi_create_int32(env, -1, &ret_napi_error);

//     NAPI_CALL_BASE(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL), ret_napi_error);

//     if(argc != 4) {
//         napi_throw_error(env, "EINVAL", "Invalid number of arguments");
//         return ret_napi_error;
//     }

//     // get the length of filename
//     NAPI_CALL_BASE(env, napi_get_value_string_utf8(env, argv[0], NULL, 0, &temp), ret_napi_error);
//     filename = (char *)malloc((temp + 1) * sizeof(char));
//     NAPI_CALL_BASE(env, napi_get_value_string_utf8(env, argv[0], filename, temp + 1, &temp), ret_napi_error);
//     filename[temp] = '\0';

//     // get the length of key_data
//     NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], NULL, 0, &temp), ret_napi_error);
//     key_data = (char *)malloc(temp * sizeof(char));
//     NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[1], key_data, temp + 1, &temp), ret_napi_error);

//     // get the length of t_data
//     NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], NULL, 0, &temp), ret_napi_error);
//     t_data = (char *)malloc(temp * sizeof(char));
//     NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[2], t_data, temp + 1, &temp), ret_napi_error);
    
//     // get the length of tag_data
//     NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[3], NULL, 0, &temp), ret_napi_error);
//     tag_data = (char *)malloc(temp * sizeof(char));
//     NAPI_CALL_BASE(env, napi_get_value_string_latin1(env, argv[3], tag_data, temp + 1, &temp), ret_napi_error);

//     // NAPI_CALL_BASE(env, napi_get_value_uint32(env, argv[4], &lambda), ret_napi_error);
//     // NAPI_CALL_BASE(env, napi_get_value_uint32(env, argv[5], &block_size), ret_napi_error);

//     #ifdef _WIN32
//         char *old_filename = filename;
//         filename = EncodingConvert(old_filename, CP_UTF8, CP_ACP);
//         free(old_filename); old_filename = NULL;
//     #endif 

//     // ret = cpor_verify(filename, key_data, t_data, tag_data, lambda, block_size);
//     ret = cpor_verify(filename, key_data, t_data, tag_data);

//     free(filename); filename = NULL;
//     free(key_data); key_data = NULL;
//     free(t_data); t_data = NULL;
//     free(tag_data); tag_data = NULL;

//     NAPI_CALL_BASE(env, napi_create_int32(env, ret, &ret_napi), ret_napi_error);

//     return ret_napi;
// }

void Init(napi_env env, napi_value exports) {
    napi_property_descriptor descCporChallenge = { "CporChallenge", 0, CporChallenge, 0, 0, 0, napi_default, 0 };
    NAPI_CALL_RETURN_VOID(env, napi_define_properties(env, exports, 1, &descCporChallenge));
    
    napi_property_descriptor descCporGetTags = { "CporGetTags", 0, CporGetTags, 0, 0, 0, napi_default, 0 };
    NAPI_CALL_RETURN_VOID(env, napi_define_properties(env, exports, 1, &descCporGetTags));
    
    napi_property_descriptor descCporProveFile = { "CporProveFile", 0, CporProveFile, 0, 0, 0, napi_default, 0 };
    NAPI_CALL_RETURN_VOID(env, napi_define_properties(env, exports, 1, &descCporProveFile));
    
    napi_property_descriptor descCporVerifyFile = { "CporVerifyFile", 0, CporVerifyFile, 0, 0, 0, napi_default, 0 };
    NAPI_CALL_RETURN_VOID(env, napi_define_properties(env, exports, 1, &descCporVerifyFile));

    // napi_property_descriptor descCporVerify = { "CporVerify", 0, CporVerify, 0, 0, 0, napi_default, 0 };
    // NAPI_CALL_RETURN_VOID(env, napi_define_properties(env, exports, 1, &descCporVerify));
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
