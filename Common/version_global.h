#pragma once

#define PRODUCT_NAME            "SF Server"
#define PRUDUCT_VISIBLE_NAME    "SF Server"
#define PRODUCT_VERSION         "0.0.1"
#define PRODUCT_AUTHOR          ""
#define PRODUCT_COMPANY         ""
#define PRODUCT_DOMAIN          ""

// http://stackoverflow.com/questions/11697820/how-to-use-date-and-time-predefined-macros-in-as-two-integers-then-stri
#define PRODUCT_START_YEAR      2015
#define PRODUCT_BUILD_YEAR \
    ( \
        (__DATE__[ 7] - '0') * 1000 + \
        (__DATE__[ 8] - '0') *  100 + \
        (__DATE__[ 9] - '0') *   10 + \
        (__DATE__[10] - '0') \
    )
