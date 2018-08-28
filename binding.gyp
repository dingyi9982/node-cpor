{
  "targets": [
    {
      "target_name": "cpor",
      "sources": [ "./binding.c" ],
      'include_dirs' : [
        'libcpor/include',
      ],
      'conditions': [
        [ 'OS == "mac"', {
            'libraries': [
              '/Users/dingyi/Genaro/node-cpor_mac/libcpor/lib/mac/libcpor.a'
            ],
          },
          'OS=="linux"', {
            'libraries': [
              '/media/psf/Home/Genaro/node-cpor_linux/libcpor/lib/linux/libcpor.a'
            ],
            'ldflags': [
              '-pthread',
            ]
          },
          'OS=="win"', {
            'libraries': [
              'Y:/Genaro/node-cpor_win32/libcpor/lib/win32/libcpor.a',
              'Y:/Genaro/node-cpor_win32/libcpor/lib/win32/libcrypto.a',
              'Y:/Genaro/node-cpor_win32/libcpor/lib/win32/libcurl.a',
              'C:/Program Files/Mingw-w64/x86_64-w64-mingw32/lib/libkernel32.a',
              'C:/Program Files/Mingw-w64/lib/gcc/x86_64-w64-mingw32/4.9.1/libgcc.a',
              'C:/Program Files/Mingw-w64/x86_64-w64-mingw32/lib/libmsvcr110.a',
              'C:/Program Files/Mingw-w64/x86_64-w64-mingw32/lib/libws2_32.a',
              'C:/Program Files/Mingw-w64/x86_64-w64-mingw32/lib/libadvapi32.a',
              'C:/Program Files/Mingw-w64/x86_64-w64-mingw32/lib/libcrypt32.a',
              'C:/Program Files/Mingw-w64/x86_64-w64-mingw32/lib/libmingwex.a',
              'C:/Program Files/Mingw-w64/x86_64-w64-mingw32/lib/libpthread.dll.a'
            ],
            'configurations': {
              'Debug': {
                'msvs_settings': {
                  'VCCLCompilerTool': {
                    'RuntimeLibrary': 3
                  },
                  'VCLinkerTool': {
                    'OutputFile': 'cpor.node'
                  }
                }
              },
              'Release': {
                'msvs_settings': {
                  'VCCLCompilerTool': {
                    'RuntimeLibrary': 2
                  },
                  'VCLinkerTool': {
                    'OutputFile': 'cpor.node'
                  }
                }
              }
            }
          }
        ]
      ]
    }
  ]
}
