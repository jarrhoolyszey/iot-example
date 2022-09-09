Import("env")

print("set_env is defining some parameters...")

env.Append(CPPDEFINES=[
  ('WIFI_SSID', env.StringifyMacro('virus')),
  ('WIFI_PSWD', env.StringifyMacro('repolhos123')),

  ('CMB_PHONE', env.StringifyMacro('+5511978789434')),
  ('CMB_API_KEY', env.StringifyMacro('476436'))
])

print("parameters defined!")