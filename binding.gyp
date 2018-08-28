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
              '/Users/dingyi/Genaro/node-cpor_linux/libcpor/lib/linux/libcpor.a'
            ],
            'ldflags': [
              '-pthread',
            ]
          },
          'OS=="win"', {
            'libraries': [
              '/Users/dingyi/Genaro/node-cpor_win32/libcpor/lib/win32/libcpor.a'
            ]
          }
        ]
      ]
    }
  ]
}
