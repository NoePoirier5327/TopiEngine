extern "C" {
  #include <lua5.4/lua.h>
  #include <lua5.4/lauxlib.h>
}

static int hello_lua(lua_State *L) {
  lua_pushstring(L, "Hello world!");
  return 1;
}

extern "C" int luaopen_topi(lua_State *L) {
  luaL_Reg functions[] = {
    {"hello", hello_lua},
    {NULL, NULL}
  };

  luaL_newlib(L, functions);
  return 1;
}
