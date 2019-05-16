
add_subdirectory(01_CaculateCode)              	#添加一个子目录
add_subdirectory(02_AnalysisClass)
add_subdirectory(03_OperateExcel)
add_subdirectory(05_CaculateMD5)


SET_PROPERTY(TARGET 01_CaculateCode  PROPERTY FOLDER "CPP_Space")  
SET_PROPERTY(TARGET 02_AnalysisClass  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET 03_OperateExcel  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET 05_CaculateMD5  PROPERTY FOLDER "CPP_Space")

SET_PROPERTY(TARGET Box2D  PROPERTY FOLDER "TmingEngine/3Part")
SET_PROPERTY(TARGET lua  PROPERTY FOLDER "TmingEngine/3Part")
