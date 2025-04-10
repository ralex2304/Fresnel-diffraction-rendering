add_library(fdr-defaults INTERFACE)

target_compile_features(fdr-defaults INTERFACE cxx_std_20)

target_compile_options(fdr-defaults
    INTERFACE
        -fdiagnostics-color=always

        -Wall
        -Wextra
        -Werror=vla
        -Wstrict-aliasing
        -Wsign-promo
        -Wpointer-arith
        -Wpointer-arith
        -Woverloaded-virtual
        -Wnon-virtual-dtor
        -Wno-missing-field-initializers
        -Wlogical-op
        -Wignored-qualifiers
        -Wformat=2
        -Wformat-security
        -Wempty-body
        -Wctor-dtor-privacy
        -Wconversion
        -Wcast-qual
        -Wmain
        -Wswitch-enum
        -Wswitch-default
        -Wfloat-equal
        -Winline
        -Wunreachable-code
        -Wmissing-declarations
        -Wmissing-include-dirs
        -Wfloat-equal
        -Winline
        -Wunreachable-code
        -Wmissing-declarations
        -Wmissing-include-dirs

        -fstack-protector-strong
        -fcheck-new
        -fstrict-overflow

        $<$<CONFIG:Debug>:
            -Og
            -g3
            -ggdb
        >

        $<$<CONFIG:Release>:
            -O2
            -march=native
            -flto
            -DNDEBUG
        >
)

target_link_options(fdr-defaults
    INTERFACE
        $<$<CONFIG:Debug>:
            -Og
            -g3
            -ggdb
        >

        $<$<CONFIG:Release>:
            -O2
            -march=native
            -flto
        >
)

