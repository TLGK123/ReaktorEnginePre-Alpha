
add_subdirectory(01_CaculateCode)              	#添加一个子目录
add_subdirectory(02_AnalysisClass)
add_subdirectory(03_OperateExcel)
add_subdirectory(05_CaculateMD5)
add_subdirectory(06_MonoRuntime)
add_subdirectory(07_TinyRender)
add_subdirectory(08_SDLMainTest)
add_subdirectory(09_ChezTest)

SET_PROPERTY(TARGET 01_CaculateCode  PROPERTY FOLDER "CPP_Space")  
SET_PROPERTY(TARGET 02_AnalysisClass  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET 03_OperateExcel  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET 05_CaculateMD5  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET 06_MonoRuntime  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET 07_TinyRender  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET 08_SDLMainTest  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET 09_ChezTest  PROPERTY FOLDER "CPP_Space")
