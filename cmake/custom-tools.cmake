cmake_minimum_required( VERSION 3.0.2 )


macro( load_config CONFIG_PATH CONFIG_TEMPLATE_PATH )
    
    if ( NOT EXISTS ${CONFIG_PATH} )
        configure_file( ${CONFIG_TEMPLATE_PATH} ${CONFIG_PATH} )
    endif()
    
    file( STRINGS ${CONFIG_PATH} CONFIG_CONTENT )
    foreach( CONFIG_LINE ${CONFIG_CONTENT} )
        string( REGEX REPLACE "^[ ]+" "" CONFIG_LINE ${CONFIG_LINE} )
        string( REGEX MATCH "^[^=]+" CONFIG_KEY ${CONFIG_LINE} ) 
        string( REPLACE "${CONFIG_KEY}=" "" CONFIG_VALUE ${CONFIG_LINE} )
        string( REGEX REPLACE " " "" CONFIG_KEY   "${CONFIG_KEY}" )
        string( REGEX REPLACE " " "" CONFIG_VALUE  "${CONFIG_VALUE}" )
        
        set( ${CONFIG_KEY} ${CONFIG_VALUE} )
        #message( "${CONFIG_KEY} = ${CONFIG_VALUE}" )
    endforeach()
    
endmacro()


macro( apply_source_groups USER_FILES DIRECTORY GROUP_PREFIX )

    foreach( USER_FILE ${${USER_FILES}} )
        file( RELATIVE_PATH SRC_GROUP ${DIRECTORY} ${USER_FILE} )
        set( SRC_GROUP "${GROUP_PREFIX}/${SRC_GROUP}" )
        string( REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRC_GROUP ${SRC_GROUP} )
        string( REPLACE / \\ SRC_GROUP ${SRC_GROUP} )
        source_group( "${SRC_GROUP}" FILES ${USER_FILE} )
    endforeach()

endmacro()
