cmake_minimum_required(VERSION 2.8)

include(CryptoNoteWallet.cmake)


project(${CN_PROJECT_NAME})

execute_process(COMMAND git log -1 --pretty=format:%h
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
OUTPUT_VARIABLE GIT_REVISION)

set(CRYPTONOTE_LIB cryptonote)
set (CMAKE_PREFIX_PATH "C://Qt//Qt5.7.1//5.7//msvc2015_64")

include_directories(${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    src
    pkcli/external
    pkcli/include
    pkcli/src)

find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
if(WIN32)
  set(Boost_USE_STATIC_RUNTIME OFF)
else(WIN32)
  set(Boost_USE_STATIC_RUNTIME ON)
endif(WIN32)

find_package(Boost 1.55 REQUIRED COMPONENTS date_time filesystem program_options regex serialization system thread chrono)
if ((${Boost_MAJOR_VERSION} EQUAL 1) AND (${Boost_MINOR_VERSION} EQUAL 54))
  message(SEND_ERROR "Boost version 1.54 is unsupported, more details are available here http://goo.gl/RrCFmA")
endif ()

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set(VERSION "")
configure_file("pkcli/src/version.h.in" "version.h")
configure_file("src/CryptoNoteWalletConfig.h.in" "CryptoNoteWalletConfig.h")

add_definitions(-DVERSION=\"${CN_VERSION}\")
add_definitions(-DGIT_REVISION=\"${GIT_REVISION}\")

set(CMAKE_AUTOMOC ON)

set(CRYPTONOTE_SOURCES
  pkcli/external/miniupnpc/connecthostport.c
  pkcli/external/miniupnpc/igd_desc_parse.c
  pkcli/external/miniupnpc/minisoap.c
  pkcli/external/miniupnpc/miniupnpc.c
  pkcli/external/miniupnpc/miniwget.c
  pkcli/external/miniupnpc/minixml.c
  pkcli/external/miniupnpc/portlistingparse.c
  pkcli/external/miniupnpc/receivedata.c
  pkcli/external/miniupnpc/upnpcommands.c
  pkcli/external/miniupnpc/upnpreplyparse.c
  pkcli/src/Common/Base58.cpp
  pkcli/src/Common/CommandLine.cpp
  pkcli/src/Common/Util.cpp
  pkcli/src/Common/StringTools.cpp
  pkcli/src/Common/JsonValue.cpp
  pkcli/src/Common/ConsoleTools.cpp
  pkcli/src/Common/MemoryInputStream.cpp
  pkcli/src/Common/PathTools.cpp
  pkcli/src/Common/DnsTools.cpp
  pkcli/src/Common/StdInputStream.cpp
  pkcli/src/Common/StdOutputStream.cpp
  pkcli/src/Common/StreamTools.cpp
  pkcli/src/Common/StringOutputStream.cpp
  pkcli/src/Common/StringView.cpp
  pkcli/src/Common/VectorOutputStream.cpp
  pkcli/src/crypto/aesb.c  
  pkcli/src/crypto/blake256.c
  pkcli/src/crypto/chacha.c
  pkcli/src/crypto/crypto-ops-data.c
  pkcli/src/crypto/crypto-ops.c
  pkcli/src/crypto/crypto.cpp
  pkcli/src/crypto/groestl.c
  pkcli/src/crypto/hash-extra-blake.c
  pkcli/src/crypto/hash-extra-groestl.c
  pkcli/src/crypto/hash-extra-jh.c
  pkcli/src/crypto/hash-extra-skein.c
  pkcli/src/crypto/hash.c
  pkcli/src/crypto/jh.c
  pkcli/src/crypto/keccak.c
  pkcli/src/crypto/aesb.c
  pkcli/src/crypto/oaes_lib.c
  pkcli/src/crypto/random.c
  pkcli/src/crypto/skein.c
  pkcli/src/crypto/slow-hash.c
  pkcli/src/crypto/slow-hash.cpp
  pkcli/src/crypto/tree-hash.c
  pkcli/src/CryptoNoteCore/BlockchainIndices.cpp
  pkcli/src/CryptoNoteCore/BlockchainMessages.cpp
  pkcli/src/CryptoNoteCore/BlockIndex.cpp
  pkcli/src/CryptoNoteCore/CoreConfig.cpp
  pkcli/src/CryptoNoteCore/CryptoNoteBasic.cpp
  pkcli/src/CryptoNoteCore/CryptoNoteTools.cpp
  pkcli/src/CryptoNoteCore/Currency.cpp
  pkcli/src/CryptoNoteCore/DepositIndex.cpp
  pkcli/src/CryptoNoteCore/MinerConfig.cpp
  pkcli/src/CryptoNoteCore/Transaction.cpp
  pkcli/src/CryptoNoteCore/Account.cpp
  pkcli/src/CryptoNoteCore/Blockchain.cpp
  pkcli/src/CryptoNoteCore/Checkpoints.cpp
  pkcli/src/CryptoNoteCore/CryptoNoteBasicImpl.cpp
  pkcli/src/CryptoNoteCore/Core.cpp
  pkcli/src/CryptoNoteCore/CryptoNoteFormatUtils.cpp
  pkcli/src/CryptoNoteCore/CryptoNoteSerialization.cpp
  pkcli/src/CryptoNoteCore/Difficulty.cpp
  pkcli/src/CryptoNoteCore/IBlock.cpp
  pkcli/src/CryptoNoteCore/Miner.cpp
  pkcli/src/CryptoNoteCore/TransactionExtra.cpp
  pkcli/src/CryptoNoteCore/TransactionPool.cpp
  pkcli/src/CryptoNoteCore/TransactionPrefixImpl.cpp
  pkcli/src/CryptoNoteCore/TransactionUtils.cpp
  pkcli/src/InProcessNode/InProcessNode.cpp
  pkcli/src/InProcessNode/InProcessNodeErrors.cpp
  pkcli/src/NodeRpcProxy/NodeErrors.cpp
  pkcli/src/NodeRpcProxy/NodeRpcProxy.cpp
  pkcli/src/P2p/NetNodeConfig.cpp
  pkcli/src/Serialization/BinaryInputStreamSerializer.cpp
  pkcli/src/Serialization/BinaryOutputStreamSerializer.cpp
  pkcli/src/Serialization/JsonInputValueSerializer.cpp
  pkcli/src/Serialization/JsonOutputStreamSerializer.cpp
  pkcli/src/Serialization/KVBinaryInputStreamSerializer.cpp
  pkcli/src/Serialization/KVBinaryOutputStreamSerializer.cpp
  pkcli/src/Serialization/SerializationOverloads.cpp
  pkcli/src/Transfers/BlockchainSynchronizer.cpp
  pkcli/src/Transfers/SynchronizationState.cpp
  pkcli/src/Transfers/TransfersConsumer.cpp
  pkcli/src/Transfers/TransfersContainer.cpp
  pkcli/src/Transfers/TransfersSubscription.cpp
  pkcli/src/Transfers/TransfersSynchronizer.cpp
  pkcli/src/Wallet/LegacyKeysImporter.cpp
  pkcli/src/Wallet/WalletAsyncContextCounter.cpp
  pkcli/src/Wallet/WalletErrors.cpp
  pkcli/src/WalletLegacy/KeysStorage.cpp
  pkcli/src/WalletLegacy/WalletLegacy.cpp
  pkcli/src/WalletLegacy/WalletHelper.cpp
  pkcli/src/WalletLegacy/WalletLegacySerializer.cpp
  pkcli/src/WalletLegacy/WalletLegacySerialization.cpp
  pkcli/src/WalletLegacy/WalletTransactionSender.cpp
  pkcli/src/WalletLegacy/WalletUnconfirmedTransactions.cpp
  pkcli/src/WalletLegacy/WalletUserTransactionsCache.cpp
  pkcli/src/System/ContextGroup.cpp
  pkcli/src/System/Event.cpp
  pkcli/src/System/EventLock.cpp
  pkcli/src/System/InterruptedException.cpp
  pkcli/src/System/Ipv4Address.cpp
  pkcli/src/System/TcpStream.cpp
  pkcli/src/HTTP/HttpRequest.cpp
  pkcli/src/HTTP/HttpParser.cpp
  pkcli/src/HTTP/HttpParserErrorCodes.cpp
  pkcli/src/HTTP/HttpResponse.cpp
  pkcli/src/Rpc/HttpClient.cpp
  pkcli/src/Rpc/JsonRpc.cpp
  pkcli/src/P2p/NetNode.cpp
  pkcli/src/P2p/LevinProtocol.cpp
  pkcli/src/P2p/NetNodeConfig.cpp
  pkcli/src/P2p/PeerListManager.cpp
  pkcli/src/CryptoNoteProtocol/CryptoNoteProtocolHandler.cpp
  pkcli/src/Logging/ILogger.cpp
  pkcli/src/Logging/LoggerGroup.cpp
  pkcli/src/Logging/CommonLogger.cpp
  pkcli/src/Logging/LoggerManager.cpp
  pkcli/src/Logging/FileLogger.cpp
  pkcli/src/Logging/StreamLogger.cpp
  pkcli/src/Logging/ConsoleLogger.cpp
  pkcli/src/Logging/LoggerMessage.cpp
  pkcli/src/Logging/LoggerRef.cpp
  pkcli/src/BlockchainExplorer/BlockchainExplorer.cpp
  pkcli/src/BlockchainExplorer/BlockchainExplorerDataBuilder.cpp
  pkcli/src/BlockchainExplorer/BlockchainExplorerErrors.cpp
)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE FORMS src/gui/ui/*.ui)

set(QRC src/resources.qrc)

qt5_wrap_ui(UIS ${FORMS})
qt5_add_resources(RCC ${QRC})


if (WIN32)
  if (NOT MSVC)
  message(FATAL_ERROR "Only MSVC is supported on this platform")
  endif ()
  add_definitions(/D_CRT_SECURE_NO_WARNINGS /D_WIN32_WINNT=0x0600 /DSTATICLIB)
  include_directories(pkcli/src/platform/msc)

  set(PLATFORM_DIR Windows)
  set(BUILD_PLATFORM WIN32)
  set(BUILD_RESOURCES src/cryptonotewallet.rc)
  set(QTMAIN Qt5::WinMain)

elseif (UNIX)
  set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} pkcli/external/miniupnpc/minissdpc.c)
  if (APPLE)
    enable_language(ASM)
    file(GLOB_RECURSE OBJC_SOURCES src/*.mm)
    set(SOURCES ${SOURCES} ${OBJC_SOURCES})
    set(PLATFORM_DIR OSX)
    set(MACOSX_BUNDLE_INFO_STRING "Cryptonote GUI wallet")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${VERSION_VERSION}.${VERSION_MINOR}.${VERSION_PATCH}")
    set(MACOSX_BUNDLE_BUNDLE_NAME CryptonoteWallet)
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION_VERSION}.${VERSION_MINOR}.${VERSION_PATCH}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "$${VERSION_VERSION}.${VERSION_MINOR}.${VERSION_PATCH}")

    find_package(Qt5PrintSupport REQUIRED)

    include_directories(/usr/include/malloc)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11 -stdlib=libc++")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -maes -D_DARWIN_C_SOURCE")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework CoreFoundation -framework Carbon -framework IOKit -L/usr/lib")

    set(MACOSX_BUNDLE_ICON_FILE cryptonote.icns)
    set(APPLICATION_ICON src/images/cryptonote.icns)
    set_source_files_properties(${APPLICATION_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    set(BUILD_PLATFORM MACOSX_BUNDLE)
    set(BUILD_RESOURCES ${APPLICATION_ICON})
  
    GET_TARGET_PROPERTY(QT_LIB_DIR "${Qt5Widgets_LIBRARIES}" LOCATION)
    GET_FILENAME_COMPONENT(QT_LIB_DIR "${QT_LIB_DIR}" PATH)
  else(APPLE)
    set(PLATFORM_DIR Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -std=c11")
  endif (APPLE)
endif ()

include_directories(pkcli/src/Platform/${PLATFORM_DIR})
file(GLOB PLATFORM_SOURCES pkcli/src/Platform/${PLATFORM_DIR}/System/*)
set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} ${PLATFORM_SOURCES})



add_library(${CRYPTONOTE_LIB} STATIC ${CRYPTONOTE_SOURCES})
if (APPLE OR ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
target_link_libraries(${CRYPTONOTE_LIB} ${Boost_LIBRARIES} -lresolv)
else ()
target_link_libraries(${CRYPTONOTE_LIB} ${Boost_LIBRARIES})
endif ()

set_target_properties(${CRYPTONOTE_LIB} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)


add_executable(${PROJECT_NAME} ${BUILD_PLATFORM} ${BUILD_RESOURCES} ${SOURCES} ${HEADERS} ${UIS} ${RCC})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${QTMAIN} ${CRYPTONOTE_LIB} ${QRENCODE_LIB})

if (APPLE)
  qt5_use_modules(${PROJECT_NAME} PrintSupport)
elseif (UNIX)
  target_link_libraries(${PROJECT_NAME} -lpthread)
elseif (WIN32)
  target_link_libraries(${PROJECT_NAME} Imm32 Iphlpapi Winmm)
endif (APPLE)

# qt5_use_modules(${PROJECT_NAME} Widgets Gui Network)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Network)


# Installation

set(CPACK_PACKAGE_NAME ${CN_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${CN_VERSION})
set(CPACK_PACKAGE_VENDOR "Pennykoin")
set(CPACK_PACKAGE_CONTACT "https://pennykoin.com/")
set(CPACK_STRIP_FILES ON)
if (APPLE)
    set(CPACK_GENERATOR DragNDrop)
    install(TARGETS ${PROJECT_NAME} BUNDLE DESTINATION .)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}.-${VERSION_RELEASE}")
elseif (UNIX)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
    install(FILES src/QTpenny.desktop DESTINATION share/applications)
    install(FILES src/images/cryptonote.png DESTINATION share/pixmaps RENAME pennykoin.png)


	SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
	SET(CPACK_PACKAGE_ICON src/images/cryptonote.png)
	
    if (NOT PACKRPM)
        set(CPACK_GENERATOR DEB)
        set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
        set(CPACK_SYSTEM_NAME amd64)
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR} <admin@pennykoin.com>")
        set(CPACK_DEBIAN_PACKAGE_SECTION Office)
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
        set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "KoinPurse is a GUI wallet for pennykoin cryptocurrency.")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${VERSION_RELEASE}.${CPACK_SYSTEM_NAME}")
	else ()
        set(CPACK_GENERATOR RPM)
        set(CPACK_SYSTEM_NAME x86_64)
        set(CPACK_RPM_PACKAGE_RELEASE ${VERSION_RELEASE})
        set(CPACK_RPM_PACKAGE_LICENSE "GPL3")
        set(CPACK_RPM_PACKAGE_GROUP Office)
        set(CPACK_RPM_PACKAGE_REQUIRES "qt5-qtbase >= 5.3.2, qt5-qtbase-gui >= 5.3.2")
        set(CPACK_RPM_PACKAGE_SUMMARY "Pennykoin GUI wallet")
        set(CPACK_RPM_PACKAGE_DESCRIPTION "QTPenny is the GUI wallet for pennykoin cryptocurrency.")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${VERSION_RELEASE}.${CPACK_SYSTEM_NAME}")
    endif ()
elseif (WIN32)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
  set(CPACK_GENERATOR ZIP)
endif (APPLE)

include(CPack)
