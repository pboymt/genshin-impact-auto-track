{
    'targets': [
        {
            'target_name': 'genshin-impact-auto-track',
            'sources': ['src/main.cc', 'src/unsafe.cc'],
            'include_dirs': [
                "<!@(node -p \"require('node-addon-api').include\")",
                "../cvAutoTrack"
            ],
            'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
            'cflags!': ['-fno-exceptions'],
            'cflags_cc!': ['-fno-exceptions'],
            'defines': [
                "NAPI_DISABLE_CPP_EXCEPTIONS"
            ],
            'xcode_settings': {
                'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                'CLANG_CXX_LIBRARY': 'libc++',
                'MACOSX_DEPLOYMENT_TARGET': '10.7'
            },
            "conditions": [
                ["OS==\"win\"", {
                    "defines": [
                        "_HAS_EXCEPTIONS=1"
                    ],
                    "msvs_settings": {
                        "VCCLCompilerTool": {
                            "ExceptionHandling": 1
                        },
                    },
                    "libraries": ["<(module_root_dir)/cvAutoTrack/CVAUTOTRACK.lib"],
                    "copies": [
                        {
                            "destination": "<(PRODUCT_DIR)/",
                            "files": ["<(module_root_dir)/cvAutoTrack/CVAUTOTRACK.dll"]
                        }
                    ]
                }]
            ]
        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": ["<(module_name)"],
            "copies": [
                {
                    "files": ["<(PRODUCT_DIR)/<(module_name).node"],
                    "destination": "<(module_path)"
                },
                {
                    "files": ["<(PRODUCT_DIR)/CVAUTOTRACK.dll"],
                    "destination": "<(module_path)"
                }
            ]
        }
        # {
        #     "target_name": "merge_binaries",
        #     "type": 'none',
        #     # test is built before this target is built
        #     "dependencies": ['genshin-impact-auto-track'],
        #     "copies":[
        #             {
        #                 "destination": "<(module_root_dir)/build/release/<(arch)",
        #                 "files": [
        #                     "../<(arch)/release/CVAUTOTRACK.dll.dll"
        #                 ]
        #             }
        #     ]
        # },
        # {
        #     "target_name": "copy_binaries",
        #     "type": 'none',
        #     # target merge_binaries is built before this target is built
        #     "dependencies": ['merge_binaries'],
        #     "copies":[
        #             {
        #                 "destination": "<(module_root_dir)/../../../../ExpressApp",
        #                 "files": [
        #                     "<(module_root_dir)/build/release/<(arch)/Extention.dll.dll",
        #                     "<(module_root_dir)/build/release/test.node"
        #                 ]
        #             }
        #     ]
        # }
    ]
}
