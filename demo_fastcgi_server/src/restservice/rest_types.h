
#ifndef _REST_TYPES_H
#define _REST_TYPES_H

#include "rest_common.h"
#include "json.h"


#define GET_TEMP_MODEL_OBJECT() j_tmpres
#define VARIABLE_UNUSED                         __attribute__ ((unused))
#define COULD_NOT_ESTABLISH_NULL_SESSION   401

json_object *j_resp,*j_arr_resp;

#define COLLECTION_INIT(METHOD) json_object *j_arr_resp = json_object_new_array(); \
    json_object *j_resp; \
    int cltn_len=0; \
    int cinc=0; \
    json_object VARIABLE_UNUSED *j_tmpres = NULL; \
    REQUEST_PARSER_INIT(METHOD);

#define MODEL_INIT(METHOD) json_object *j_resp = json_object_new_object(); \
    REQUEST_PARSER_INIT(METHOD);

//For Adding Object to  Model Object
#define MODEL_ADD_OBJECT(KEY, VALUE)            json_object_object_add(j_resp, KEY, VALUE);

//Most probably used inside a loop
#define GET_TEMP_MODEL_OBJECT() j_tmpres
#define NEW_MODEL() j_resp = json_object_new_object();
#define COLLECTION_NEW_MODEL() NEW_MODEL();

//For Adding Object to  Model Object
#define TEMP_MODEL_ADD_OBJECT(KEY, VALUE) json_object_object_add(j_tmpres, KEY, VALUE);

//Used to Create Temporary Model Output
#define NEW_TEMP_MODEL() j_tmpres = json_object_new_object();
#define TEMP_MODEL_FREE() json_obj_delete(j_tmpres);

#define TEMP_MODEL_ADD_STRING_LEN(KEY, VALUE, LEN) TEMP_MODEL_ADD_OBJECT(KEY, json_object_new_string_len(VALUE, LEN))
#define TEMP_MODEL_ADD_STRING(KEY, VALUE) TEMP_MODEL_ADD_OBJECT(KEY, json_object_new_string_len(VALUE, strlen(VALUE)))
#define TEMP_MODEL_ADD_INT(KEY, VALUE)TEMP_MODEL_ADD_OBJECT(KEY, json_object_new_int(VALUE))
#define TEMP_MODEL_ADD_BOOLEAN(KEY, VALUE)TEMP_MODEL_ADD_OBJECT(KEY, (json_bool) VALUE)
#define TEMP_MODEL_ADD_BOOL(KEY, VALUE)TEMP_MODEL_ADD_BOOLEAN(KEY, VALUE)
#define TEMP_MODEL_ADD_INTEGER(KEY, VALUE)TEMP_MODEL_ADD_INT(KEY, VALUE)
#define TEMP_MODEL_ADD_NUMBER(KEY, VALUE)TEMP_MODEL_ADD_INT(KEY, VALUE)
#define TEMP_MODEL_ADD_FLOAT(KEY, VALUE)TEMP_MODEL_ADD_OBJECT(KEY, json_object_new_double(VALUE))
#define TEMP_MODEL_ADD_DOUBLE(KEY, VALUE)TEMP_MODEL_ADD_OBJECT(KEY, json_object_new_double(VALUE))

#define MODEL_ADD_TEMP_MODEL(KEY) MODEL_ADD_OBJECT(KEY, j_tmpres);

//Common for both single Model and Collection-Model
#define MODEL_ADD_MEMBER(KEY, VALUE) json_object_object_add(j_resp, KEY, VALUE);
#define MODEL_ADD_STRING(KEY, VALUE) MODEL_ADD_MEMBER(KEY, json_object_new_string_len(VALUE, strlen(VALUE)))
#define MODEL_ADD_STR(KEY, VALUE) MODEL_ADD_STRING(KEY, VALUE)
#define MODEL_ADD_BOOLEAN(KEY, VALUE) MODEL_ADD_MEMBER(KEY, json_object_new_boolean(VALUE))
#define MODEL_ADD_BOOL(KEY, VALUE) MODEL_ADD_BOOLEAN(KEY, VALUE)
#define MODEL_ADD_INT(KEY, VALUE) MODEL_ADD_MEMBER(KEY, json_object_new_int(VALUE))
#define MODEL_ADD_INTEGER(KEY, VALUE) MODEL_ADD_INT(KEY, VALUE)
#define MODEL_ADD_NUMBER(KEY, VALUE) MODEL_ADD_INT(KEY, VALUE)
#define MODEL_ADD_FLOAT(KEY, VALUE) MODEL_ADD_MEMBER(KEY, json_object_new_double(VALUE))
#define MODEL_ADD_DOUBLE(KEY, VALUE) MODEL_ADD_MEMBER(KEY, json_object_new_double(VALUE))

#define RESPONSE_ADD_MEMBER(KEY, VALUE) json_object_object_add(req_json, KEY, VALUE);
#define RESPONSE_ADD_STRING(KEY, VALUE) RESPONSE_ADD_MEMBER(KEY, json_object_new_string_len(VALUE, strlen(VALUE)))
#define RESPONSE_ADD_STR(KEY, VALUE) RESPONSE_ADD_STRING(KEY, VALUE)
#define RESPONSE_ADD_BOOLEAN(KEY, VALUE) RESPONSE_ADD_MEMBER(KEY, (json_bool) VALUE)
#define RESPONSE_ADD_BOOL(KEY, VALUE) RESPONSE_ADD_BOOLEAN(KEY, VALUE)
#define RESPONSE_ADD_INT(KEY, VALUE) RESPONSE_ADD_MEMBER(KEY, json_object_new_int(VALUE))
#define RESPONSE_ADD_INTEGER(KEY, VALUE) RESPONSE_ADD_INT(KEY, VALUE)
#define RESPONSE_ADD_NUMBER(KEY, VALUE) RESPONSE_ADD_INT(KEY, VALUE)
#define RESPONSE_ADD_FLOAT(KEY, VALUE) RESPONSE_ADD_MEMBER(KEY, json_object_new_double(VALUE))
#define RESPONSE_ADD_DOUBLE(KEY, VALUE) RESPONSE_ADD_MEMBER(KEY, json_object_new_double(VALUE))


#define COLLECTION_ADD_MODEL() json_object_array_add(j_arr_resp, j_resp);

#define COLLECTION_PUSH_MODEL(model) json_object_array_add(j_arr_resp, model);

#define COLLECTION_SET_DATA(cltn) json_object_put(j_arr_resp); \
    j_arr_resp = cltn;

#define COLLECTION_TO_STRING() json_object_to_json_string(j_arr_resp)

#define MODEL_TO_STRING() json_object_to_json_string(j_resp)

#define REQUEST_TO_STRING() json_object_to_json_string(req_json)

//Free all model and collection. Use with COLLECTION_INIT()
#define COLLECTION_FREE() cltn_len=json_object_array_length(j_arr_resp); \
                                   for(cinc=0; cinc<cltn_len; cinc++) { \
                                    json_object_put(json_object_array_get_idx(j_arr_resp, cinc)); \
                                   } \
                                    json_object_put(j_arr_resp); \
                                    REQUEST_PARSER_FREE();

//Free only one model. Use with MODEL_INIT()
#define MODEL_FREE() if(j_resp != NULL) json_object_put(j_resp); \
    REQUEST_PARSER_FREE();


//OUTPUT Collection. Use with COLLECTION_INIT()
#define COLLECTION_OUTPUT() SUCCESS_OUTPUT(COLLECTION_TO_STRING());

//OUTPUT Model. Use with MODEL_INIT()
#define MODEL_OUTPUT() SUCCESS_OUTPUT(MODEL_TO_STRING());

//OUTPUT Incoming Request. Typically used when incoming request is saved successfully.(PUT/POST)
#define SAVE_SUCCEEDED_OUTPUT() \
    char *getenvptr=getenv("REQUEST_METHOD");\
    char *getenvptr1=getenv("CONTENT_TYPE");\
    if((getenvptr!=NULL) && (getenvptr1!=NULL) && strcasecmp(getenvptr, "GET") != 0 && strncasecmp(getenvptr1, "application/json", strlen("application/json")) == 0){\
        SUCCESS_OUTPUT(REQUEST_TO_STRING()); \
    }

#define UPLOAD_OUTPUT() \
    json_object *jresp = json_object_new_object(); \
    qcgires_setcontenttype(req, "application/json"); \
    json_object_object_add(jresp,"cc",json_object_new_int(0)); \
    printf("%s",json_object_to_json_string(jresp)); \
    json_object_put(jresp);

#define START_MODEL(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    START_HANDLER(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS); \
    MODEL_INIT(METHOD);

#define END_MODEL \
    MODEL_FREE(); \
goto end_handler; \
end_handler: \
    END_HANDLER

#define START_AUTHORIZED_FILE_DOWNLOAD(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS, DOWNLOAD, FILE_PATH) \
    START_HANDLER_AUTHORIZED(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS); \
    MODEL_INIT(METHOD); \
    AUTHORIZATION_MODEL_INIT(); \
    char *path = FILE_PATH; \
    int dl = DOWNLOAD;

#define THROW_FILE_DOWNLOAD_ERROR(STATUS, ERROR_MSG, ERROR_CODE) \
    THROW_MODEL_ERROR(STATUS, ERROR_MSG, ERROR_CODE);

#define END_AUTHORIZED_FILE_DOWNLOAD \
    if(dl) \
        printf("content-disposition: attachment\r\n"); \
    printf("X-Sendfile2: %s 0-\r\n\r\n", path); \
    MODEL_FREE(); \
    END_AUTHORIZED_MODEL \

#define START_AUTHORIZED_FILE_DOWNLOAD_WITH_CUSTOM_PATH(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS, DOWNLOAD, FILE_PATH) \
    START_HANDLER_AUTHORIZED(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS); \
    MODEL_INIT(METHOD); \
    AUTHORIZATION_MODEL_INIT(); \
    char *path = FILE_PATH; \
    int dl = DOWNLOAD;

#define THROW_FILE_DOWNLOAD_ERROR(STATUS, ERROR_MSG, ERROR_CODE) \
    THROW_MODEL_ERROR(STATUS, ERROR_MSG, ERROR_CODE);

#define END_AUTHORIZED_FILE_DOWNLOAD_WITH_CUSTOM_PATH \
    if(dl) \
        printf("content-disposition: attachment\r\n"); \
    printf("X-Sendfile2: %s 0-\r\n\r\n", path); \
	if(path != NULL) { \
        free(path); \
        path = NULL; \
    } \
    MODEL_FREE(); \
    END_AUTHORIZED_MODEL \

#define START_AUTHORIZED_NO_MODEL(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    START_HANDLER_AUTHORIZED(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS); \
    MODEL_INIT(METHOD); \

#define END_AUTHORIZED_NO_MODEL \
    MODEL_FREE(); \
goto end_handler; \
end_handler: \
    END_HANDLER_AUTHORIZED


#define START_AUTHORIZED_MODEL(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    START_HANDLER_AUTHORIZED(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS); \
    MODEL_INIT(METHOD); \
    AUTHORIZATION_MODEL_INIT(); \

#define END_AUTHORIZED_MODEL \
    AUTHORIZATION_MODEL_FIN(); \
    MODEL_FREE(); \
goto end_handler; \
end_handler: \
    END_HANDLER_AUTHORIZED

#define END_NOOP_AUTHORIZED_MODEL \
    AUTHORIZATION_MODEL_FIN(); \
    MODEL_FREE(); \
goto end_handler; \
end_handler: \
end_handler_auth: \
    END_HANDLER

#define START_COLLECTION(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    START_HANDLER(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS); \
    COLLECTION_INIT(METHOD);

#define END_COLLECTION \
    COLLECTION_FREE(); \
goto end_handler; \
end_handler: \
    END_HANDLER

#define START_AUTHORIZED_NO_COLLECTION(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    START_HANDLER_AUTHORIZED(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    COLLECTION_INIT(METHOD); \

#define END_AUTHORIZED_NO_COLLECTION \
    COLLECTION_FREE(); \
goto end_handler; \
end_handler: \
    END_HANDLER_AUTHORIZED

#define START_AUTHORIZED_COLLECTION(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    START_HANDLER_AUTHORIZED(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    COLLECTION_INIT(METHOD); \
    AUTHORIZATION_COLLECTION_INIT(); \

#define END_AUTHORIZED_COLLECTION \
    AUTHORIZATION_COLLECTION_FIN(); \
    COLLECTION_FREE(); \
goto end_handler; \
end_handler: \
    END_HANDLER_AUTHORIZED

#define START_AUTHORIZED_POLL_COLLECTION(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    START_HANDLER_AUTHORIZED_POLL(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    COLLECTION_INIT(METHOD); \
    AUTHORIZATION_COLLECTION_INIT(); \

#define END_AUTHORIZED_POLL_COLLECTION \
    AUTHORIZATION_COLLECTION_FIN(); \
    COLLECTION_FREE(); \
goto end_handler; \
end_handler: \
    END_HANDLER_AUTHORIZED_POLL

#define START_AUTHORIZED_POLL_MODEL(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    START_HANDLER_AUTHORIZED_POLL(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    MODEL_INIT(METHOD); \
    AUTHORIZATION_MODEL_INIT(); \

#define END_AUTHORIZED_POLL_MODEL \
    AUTHORIZATION_MODEL_FIN(); \
    MODEL_FREE(); \
goto end_handler; \
end_handler: \
    END_HANDLER_AUTHORIZED_POLL


#define START_AUTHORIZED_POLL_NO_MODEL(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    START_HANDLER_AUTHORIZED_POLL(NAME, METHOD, REGEX, NUM, MATCHES, HEADERS) \
    MODEL_INIT(METHOD); \
    
#define END_AUTHORIZED_POLL_NO_MODEL \
    MODEL_FREE(); \
goto end_handler; \
end_handler: \
    END_HANDLER_AUTHORIZED_POLL

#define AUTHORIZATION_MODEL_INIT()\
    int session_result = 1;\
    if(session_result != RPC_HAPI_SUCCESS){ \
        THROW_MODEL_ERROR(STATUS_401, "Session could not be established", COULD_NOT_ESTABLISH_NULL_SESSION); \
    }\

#define AUTHORIZATION_FIN() \
     //Logout(&Session);



#define AUTHORIZATION_MODEL_FIN() \
    AUTHORIZATION_FIN();

#define AUTHORIZATION_COLLECTION_FIN() \
    AUTHORIZATION_FIN();

#define THROW_MODEL_ERROR(STATUS, ERROR_MSG, ERROR_CODE) \
	AUTHORIZATION_MODEL_FIN();\
    MODEL_FREE(); \
    NEW_MODEL(); \
    MODEL_ADD_STRING("error", ERROR_MSG); \
    MODEL_ADD_INT("code", ERROR_CODE); \
    ERROR_OUTPUT(STATUS, MODEL_TO_STRING()); \
    MODEL_FREE(); \
    goto end_handler;

#define THROW_MODEL_ERROR_WITHOUT_LOGOUT(STATUS, ERROR_MSG, ERROR_CODE) \
    MODEL_FREE(); \
    NEW_MODEL(); \
    MODEL_ADD_STRING("error", ERROR_MSG); \
    MODEL_ADD_INT("code", ERROR_CODE); \
    ERROR_OUTPUT(STATUS, MODEL_TO_STRING()); \
    MODEL_FREE(); \
    goto end_handler;

#define THROW_COLLECTION_ERROR(STATUS, ERROR_MSG, ERROR_CODE) \
	AUTHORIZATION_COLLECTION_FIN()\
    COLLECTION_FREE(); \
    NEW_MODEL(); \
    MODEL_ADD_STRING("error", ERROR_MSG); \
    MODEL_ADD_INT("code", ERROR_CODE); \
    ERROR_OUTPUT(STATUS, MODEL_TO_STRING()); \
    MODEL_FREE(); \
    goto end_handler;

#define THROW_COLLECTION_ERROR_WITHOUT_LOGOUT(STATUS, ERROR_MSG, ERROR_CODE) \
    COLLECTION_FREE(); \
    NEW_MODEL(); \
    MODEL_ADD_STRING("error", ERROR_MSG); \
    MODEL_ADD_INT("code", ERROR_CODE); \
    ERROR_OUTPUT(STATUS, MODEL_TO_STRING()); \
    MODEL_FREE(); \
    goto end_handler;

#define THROW_UPLOAD_ERROR(STATUS, ERROR_MSG, ERROR_CODE) \
    json_object *jresp = json_object_new_object(); \
    json_object_object_add(jresp,"code",json_object_new_int(ERROR_CODE)); \
    json_object_object_add(jresp,"error",json_object_new_string_len(ERROR_MSG, strlen(ERROR_MSG))); \
    ERROR_OUTPUT(STATUS, json_object_to_json_string(jresp)); \
    json_object_put(jresp); \
    goto end_handler_auth_upload; \

#define REQUEST_PARSER_INIT(METHOD)                                                   \
    char *query = qcgireq_getquery(CGI_##METHOD);                                     \
    json_object *req_json = json_object_new_object();                                 \
    json_object *req_json_var = NULL;                                                 \
    if (0) {                                                                          \
        req_json_var = req_json_var;                                                  \
    }                                                                                 \
    char *methodEnvptr = getenv("REQUEST_METHOD");                                    \
    char *contentEnvptr = getenv("CONTENT_TYPE");                                     \
    if ((methodEnvptr != NULL)) {                                                     \
        if (strcasecmp(methodEnvptr, "GET") != 0 && query != NULL) {                  \
            if ((contentEnvptr != NULL) && strcasecmp(methodEnvptr, "PUT") == 0 &&    \
                strncasecmp(contentEnvptr, "application/json",                        \
                            strlen("application/json")) == 0) {                       \
                json_object_put(req_json);                                            \
                req_json = json_tokener_parse(query);                                 \
                if (req_json == NULL) {                                               \
                    json_object *jresp_invalid_json;                                  \
                    printf("Status: 400 Bad Request \r\n");                           \
                    qcgires_setcontenttype(req, "application/json");                  \
                    jresp_invalid_json = json_object_new_object();                    \
                    json_object_object_add(jresp_invalid_json, "cc",                  \
                                           json_object_new_int(8));                   \
                    json_object_object_add(                                           \
                        jresp_invalid_json, "error",                                  \
                        json_object_new_string("Invalid JSON Message Received"));     \
                    printf("%s", json_object_to_json_string(jresp_invalid_json));     \
                    json_object_put(jresp_invalid_json);                              \
                    MODEL_FREE();                                                     \
                    goto end_handler;                                                 \
                }                                                                     \
            } else if (contentEnvptr != NULL) {                                       \
                json_object_put(req_json);                                            \
                req_json = json_tokener_parse(query);                                 \
            }                                                                         \
        } else if (strcasecmp(methodEnvptr, "PUT") == 0 && query == NULL) {           \
            json_object_put(req_json);                                                \
            json_object *jresp_invalid_json;                                          \
            printf("Status: 400 Bad Request \r\n");                                   \
            qcgires_setcontenttype(req, "application/json");                          \
            jresp_invalid_json = json_object_new_object();                            \
            json_object_object_add(jresp_invalid_json, "cc", json_object_new_int(8)); \
            json_object_object_add(                                                   \
                jresp_invalid_json, "error",                                          \
                json_object_new_string("Invalid JSON Message Received"));             \
            printf("%s", json_object_to_json_string(jresp_invalid_json));             \
            json_object_put(jresp_invalid_json);                                      \
            MODEL_FREE();                                                             \
            goto end_handler;                                                         \
        }                                                                             \
    }

#define REQUEST_PARSER_FREE()                                                  \
    char *methodEnvptr = getenv("REQUEST_METHOD");                             \
    char *contentEnvptr = getenv("CONTENT_TYPE");                              \
    char *query = qcgireq_getquery(0);                                          \
    if (query != NULL) {                                                       \
        free(query);                                                           \
        query = NULL;                                                          \
    }                                                                          \
    if ((methodEnvptr != NULL)) {                                              \
        if (strcasecmp(methodEnvptr, "GET") != 0 && (contentEnvptr != NULL)) { \
            if (strcasecmp(methodEnvptr, "PUT") == 0 &&                        \
                strncasecmp(contentEnvptr, "application/json",                 \
                            strlen("application/json")) == 0) {                \
                if (req_json != NULL) json_object_put(req_json);               \
            } else {                                                           \
                if (req_json != NULL) json_object_put(req_json);               \
            }                                                                  \
        } else {                                                               \
            if (req_json != NULL) json_object_put(req_json);                   \
        }                                                                      \
    }

// Do not free the request variables manually. Freeing is taken care by json_object_put.
//#define REQUEST_REQUIRED_VAR(VARIABLE, KEY, JSON_TYPE, JSON_FUNCTION, VARIABLE_TYPE)   \
    json_object *req_json_var = NULL;                                                  \
    json_object *req_json = json_object_new_object();                                  \
    qentry_t *req =  qcgireq_parse(NULL, (Q_CGI_T)0);                                  \
    if (json_object_object_get_ex(req_json, KEY, &req_json_var)) {                     \
        if (json_object_get_type(req_json_var) == JSON_TYPE) {                         \
            VARIABLE = (VARIABLE_TYPE JSON_FUNCTION(req_json_var));                      \
        } else {                                                                       \
            json_object *jresp_invalid_var_type;                                       \
            printf("Status: 400 Bad Request \r\n");                                    \
            qcgires_setcontenttype(req, "application/json");                           \
            jresp_invalid_var_type = json_object_new_object();                         \
            json_object_object_add(jresp_invalid_var_type, "cc",                       \
                                   json_object_new_int(8));                            \
            json_object_object_add(                                                    \
                jresp_invalid_var_type, "error",                                       \
                json_object_new_string("Invalid Variable Type Received"));             \
            printf("%s", json_object_to_json_string(jresp_invalid_var_type));          \
            json_object_put(jresp_invalid_var_type);                                   \
            MODEL_FREE();                                                              \
            goto end_handler;                                                          \
        }                                                                              \
    } else {                                                                           \
        json_object *jresp_var_not_found;                                              \
        printf("Status: 400 Bad Request \r\n");                                        \
        qcgires_setcontenttype(req, "application/json");                               \
        jresp_var_not_found = json_object_new_object();                                \
        json_object_object_add(jresp_var_not_found, "cc", json_object_new_int(8));     \
        json_object_object_add(jresp_var_not_found, "error",                           \
                               json_object_new_string("Required Variable Not Found")); \
        printf("%s", json_object_to_json_string(jresp_var_not_found));                 \
        json_object_put(jresp_var_not_found);                                          \
        MODEL_FREE();                                                                  \
        goto end_handler;                                                              \
    }                                                                                  \
    end_handler:NULL                                                                           

#define REQUEST_REQUIRED_VAR(VARIABLE, KEY, JSON_TYPE, JSON_FUNCTION, VARIABLE_TYPE) \
    json_object *req_json_var = NULL; \
    qentry_t *req =  qcgireq_parse(NULL, (Q_CGI_T)0);\
    json_object *req_json = NULL; \
    char* json_str = req->getstr(req, "json", "");\
    DEBUG_LOG(DEBUG_PATH,DEBUG,"runign.yan----get_query_string1====%s\n",json_str);\

// [TODO] As json_object_get_string return (const char *) type, we should have a same type variable to be assigned instead of doing type conversion to (char *)
#define REQUEST_REQUIRED_VAR_STRING(VARIABLE, KEY) \
    REQUEST_REQUIRED_VAR(VARIABLE, KEY, json_type_string, json_object_get_string, (char *))

#define REQUEST_REQUIRED_VAR_INTEGER(VARIABLE, KEY, VARIABLE_TYPE) \
    REQUEST_REQUIRED_VAR(VARIABLE, KEY, json_type_int, json_object_get_int, VARIABLE_TYPE)


#define REQUEST_REQUIRED_VAR_NUMBER(V) REQUEST_REQUIRED_VAR_INTEGER(V)

#define REQUEST_REQUIRED_VAR_DOUBLE(VARIABLE, KEY) \
    REQUEST_REQUIRED_VAR(VARIABLE, KEY, json_type_double, json_object_get_double, )

#define REQUEST_REQUIRED_VAR_FLOAT(V) REQUEST_REQUIRED_VAR_DOUBLE(V)

#define REQUEST_REQUIRED_VAR_BOOLEAN(VARIABLE, KEY) \
    REQUEST_REQUIRED_VAR(VARIABLE, KEY, json_type_boolean, json_object_get_boolean, )

#define REQUEST_REQUIRED_VAR_BOOL(V) REQUEST_REQUIRED_VAR_BOOLEAN(V)

#define REQUEST_REQUIRED_VAR_OBJECT(VARIABLE, KEY) \
    REQUEST_REQUIRED_VAR(VARIABLE, KEY, json_type_object, , )

#define REQUEST_REQUIRED_VAR_ARRAY(VARIABLE, KEY) \
    REQUEST_REQUIRED_VAR(VARIABLE, KEY, json_type_array, , )

#define GET_REQUEST_OBJECT() json_object_get(req_json)

#define RESOURCE_FILTER_INTEGER(POS, VALUE) char *url = get_path_info(); \
if(url != NULL){ \
char *substr = NULL; \
substr = malloc((int)matches[POS].rm_eo - (int)matches[POS].rm_so + 1); \
if (substr != NULL){\
memset(substr, 0, (int)matches[POS].rm_eo - (int)matches[POS].rm_so + 1); \
sprintf(substr, "%.*s", (int)matches[POS].rm_eo - (int)matches[POS].rm_so, url+(int)matches[POS].rm_so); \
VALUE = atol(substr); \
free(substr);\
}\
}

#define RESOURCE_INDEX_INTEGER(VALUE) RESOURCE_FILTER_INTEGER(1, VALUE);

#define RESOURCE_FILTER_STRING(POS, VALUE) char *url = get_path_info(); \
if(url != NULL && (VALUE = malloc((int)matches[POS].rm_eo - (int)matches[POS].rm_so + 1)) != NULL){\
	memset(VALUE, 0, (int)matches[POS].rm_eo - (int)matches[POS].rm_so + 1); \
	sprintf(VALUE, "%.*s", (int)matches[POS].rm_eo - (int)matches[POS].rm_so, url+(int)matches[POS].rm_so);\
}

#define RESOURCE_INDEX_STRING(VALUE) RESOURCE_FILTER_STRING(1, VALUE);

#define MAP_UPLOAD_HANDLER(HDLR) map_func(&mh##HDLR); \
add_handler(HDLR);


//placeholder for operations which are only POST based
#define START_AUTHORIZED_OPERATION START_AUTHORIZED_MODEL

#define END_AUTHORIZED_OPERATION END_AUTHORIZED_MODEL

#define THROW_OPERATION_ERROR THROW_MODEL_ERROR

//for Privilege check
#define ENFORCE_MODEL_PRIVILEGE(priv) if(sess->getint(sess, "role") < priv){THROW_MODEL_ERROR(STATUS_403, "Insufficient Privilege", INVALID_PRIVILEGE_ACCESS)}
#define ENFORCE_COLLECTION_PRIVILEGE(priv) if(sess->getint(sess, "role") < priv){THROW_COLLECTION_ERROR(STATUS_403, "Insufficient Privilege", INVALID_PRIVILEGE_ACCESS)}
#define ENFORCE_UPLOAD_PRIVILEGE(priv) if(sess->getint(sess, "role") < priv){THROW_UPLOAD_ERROR(STATUS_403, "Insufficient Privilege", INVALID_PRIVILEGE_ACCESS)}

#define ENFORCE_MODEL_FEATURECHECK(featureCheck) if(featureCheck != ENABLED){THROW_MODEL_ERROR_WITHOUT_LOGOUT(STATUS_405, "Feature is not enabled", FEATURE_NOT_ENABLED)}
#define ENFORCE_COLLECTION_FEATURECHECK(featureCheck) if(featureCheck != ENABLED){THROW_COLLECTION_ERROR(STATUS_405, "Feature is not enabled", FEATURE_NOT_ENABLED)}
#define ENFORCE_MODEL_NOT_FEATURECHECK(featureCheck) if(featureCheck == ENABLED){THROW_MODEL_ERROR(STATUS_405, "Operation is not allowed", OPERATION_NOT_ALLOW)}
#define ENFORCE_COLLECTION_NOT_FEATURECHECK(featureCheck) if(featureCheck == ENABLED){THROW_COLLECTION_ERROR(STATUS_405, "Feature is not enabled", FEATURE_NOT_ENABLED)}
#define ENFORCE_UPLOAD_FEATURECHECK(featureCheck) if(featureCheck != ENABLED){THROW_UPLOAD_ERROR(STATUS_405, "Feature is not enabled", FEATURE_NOT_ENABLED)}

#define ENFORCE_MODEL_LICENSECHECK(LicenseValidity) if(LicenseValidity == -1){ THROW_MODEL_ERROR(STATUS_500, "Error getting the licenses", COULD_NOT_GET_LICENSE_COUNT)} if(LicenseValidity == 0){  THROW_MODEL_ERROR(STATUS_12013, "License is not available", LICENSE_NOT_ENABLED)  }
#define ENFORCE_COLLECTION_LICENSECHECK(LicenseValidity) if(LicenseValidity == -1){ THROW_COLLECTION_ERROR(STATUS_500, "Error getting the licenses", COULD_NOT_GET_LICENSE_COUNT);   } if(LicenseValidity == 0){ THROW_COLLECTION_ERROR(STATUS_12013, "License is not available", LICENSE_NOT_ENABLED)      }

#define ENFORCE_UPLOAD_PRIVILEGE(priv) if(sess->getint(sess, "role") < priv){qcgires_setcontenttype(req, "application/json");THROW_UPLOAD_ERROR(STATUS_403, "Insufficient Privilege", INVALID_PRIVILEGE_ACCESS)}
#endif
