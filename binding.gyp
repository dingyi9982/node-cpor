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
              '/Users/dingyi/Genaro/node-cpor/libcpor/lib/mac/libcpor.a'
            ],
          },
          'OS=="linux"', {
            'libraries': [
              '/Users/dingyi/Genaro/node-cpor/libcpor/lib/linux/libcpor.a'
            ],
            'ldflags': [
              '-pthread',
            ]
          },
          'OS=="win"', {
            'libraries': [
              '/Users/dingyi/Genaro/node-cpor/libcpor/lib/win32/libcpor.a'
            ]
          }
        ]
      ]
    }
  ]
}
