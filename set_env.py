Import("env")

print("set_env is defining some parameters...")

env.Append(CPPDEFINES=[
  ('WIFI_SSID', env.StringifyMacro('virus')),
  ('WIFI_PSWD', env.StringifyMacro('repolhos123')),

  ('CMB_PHONE', env.StringifyMacro('+5511940645281')),
  ('CMB_TOKEN', env.StringifyMacro('291120'))
])

print("parameters defined!")