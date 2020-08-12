env = Environment()
#Program("ScriptEngine" ,['scheme.cpp' ,'main.cpp'])
env.Program("ScriptEngine" , Glob('*.cpp'), Glob('*.c'))
env.SharedLibrary("ScriptEngine" ,"scheme.cpp")