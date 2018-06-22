#pragma once

#define XML_MAX_PARAMS_CNT 32768
#define XML_MAX_PATH_DEPTH 128
#define XML_MAX_SECTION_DESC_LEN 64
#define XML_MAX_PATH_LEN XML_MAX_PATH_DEPTH*XML_MAX_SECTION_DESC_LEN
#define XML_MAX_PARAM_NAME_LEN	128
#define XML_MAX_PARAM_VAL_LEN	128
#define XML_MAX_LINE_SIZE XML_MAX_PARAM_NAME_LEN+XML_MAX_PARAM_VAL_LEN
#define XML_MAX_ARRAY_PARAM_ELEM_CNT 32

//-- get options
#define SimpleVal 8
#define EnumVal   9

