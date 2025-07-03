

set(SRCS FunctionCallObfuscate.cpp
    CryptoUtils.cpp
    BogusControlFlow.cpp
    SubstituteImpl.cpp
    Substitution.cpp
    Flattening.cpp
    Utils.cpp
    SplitBasicBlocks.cpp
    AntiClassDump.cpp
    AntiDebugging.cpp
    AntiHooking.cpp
    StringEncryption.cpp
    IndirectBranch.cpp
    FunctionWrapper.cpp
    ConstantEncryption.cpp
    Obfuscation.cpp
)

if(BUILD_ANDROID_NDK)
    add_library(Hikari MODULE ${SRCS})
else()
    add_library(Hikari SHARED ${SRCS})
endif()


target_include_directories(Hikari PRIVATE ${CMAKE_SOURCE_DIR}/obfuscation)

if(BUILD_ANDROID_NDK)
    set_target_properties(Hikari PROPERTIES
        COMPILE_FLAGS "-fno-rtti"
    )

    target_link_libraries(Hikari PRIVATE
        LLVM
    )
else()
    add_dependencies(Hikari intrinsics_gen LLVMLinker)
    llvm_map_components_to_libnames(llvm_libs core support irreader linker passes)
    target_link_libraries(Hikari PRIVATE ${llvm_libs})
endif()


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_target_properties(Hikari PROPERTIES
        LINK_FLAGS "-static -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -lstdc++ -Wl,--no-whole-archive -Wl,-Bdynamic"
    )
endif()

if(APPLE)
    set_target_properties(Hikari PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)

if(APPLE)
    add_custom_command(
        TARGET Hikari POST_BUILD
        COMMAND codesign --force --sign - $<TARGET_FILE:Hikari>
        COMMENT "Ad-hoc signing $<TARGET_FILE:Hikari> for macOS"
    )
endif()

execute_process(
        COMMAND git log -1 --format=%H
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        OUTPUT_VARIABLE HIKARI_GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
target_compile_definitions(Hikari PRIVATE "-DGIT_COMMIT_HASH=\"${HIKARI_GIT_COMMIT_HASH}\"")
