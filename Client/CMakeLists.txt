cmake_minimum_required(VERSION 4.0)
project(Client)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "E:/Qt/Qt6.10/6.5.3/mingw_64")
set(CMAKE_AUTORCC ON)
# 指定寻找UIC文件的路径
set(CMAKE_AUTOUIC_SEARCH_PATHS "Forms")
find_package(Qt6 COMPONENTS Core Gui Widgets Sql Network REQUIRED)
qt_standard_project_setup()

add_executable(Client main.cpp
        Sources/login_dialog.cpp
        Headers/login_dialog.h
        Sources/register_dialog.cpp
        Headers/register_dialog.h
        Headers/singleton.h
        Headers/global.h
        Sources/global.cpp
        Sources/httpmgr.cpp
        Headers/httpmgr.h
        Sources/Toast.cpp
        Headers/Toast.h
        Sources/TimerBtn.cpp
        Headers/TimerBtn.h
        Sources/ClickedLabel.cpp
        Headers/ClickedLabel.h
        Sources/TcpMgr.cpp
        Headers/TcpMgr.h
        Headers/usermgr.h
        Sources/usermgr.cpp
        Headers/userdata.h
        Sources/userdata.cpp
        Sources/chat_dialog.cpp
        Headers/chat_dialog.h
        Forms/chat_dialog.ui
)
target_link_libraries(Client
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
)

qt_add_resources(Client imageresources
        PREFIX "/"
        FILES image/QQ_1.png
        FILES image/004_加好友.png
        FILES image/huaji.png
        FILES image/QQ_2.png
        FILES image/表情.png
        FILES image/创建群聊.png
        FILES image/调皮.png
        FILES image/发呆.png
        FILES image/工程师.png
        FILES image/工人.png
        FILES image/可爱.png
        FILES image/苦笑.png
        FILES image/联系人.png
        FILES image/聊天记录.png
        FILES image/文件夹.png
        FILES image/消息_1.png
        FILES image/消息_2.png
        FILES image/智能机器人.png
        FILES image/组长.png
        FILES image/显示密码1.png
        FILES image/显示密码.png
        FILES image/隐藏密码.png
        FILES image/隐藏密码1.png
)

target_include_directories(Client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources
        ${CMAKE_CURRENT_SOURCE_DIR}/Headers  # <--- 关键：告诉编译器去 Headers 文件夹找 TimerBtn.h
        # 如果有其他目录也加上
)

set(TargetConfig "${CMAKE_CURRENT_SOURCE_DIR}/config.ini")
set(OutputDir "${CMAKE_CURRENT_BINARY_DIR}")
add_custom_command(TARGET Client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${TargetConfig}"
        "${OutputDir}"
        COMMENT "Copying config.ini to output directory..."
        VERBATIM
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
