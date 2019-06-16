add_subdirectory(example)              	#添加一个子目录
add_subdirectory(FileFilter)            #添加一个子目录
add_subdirectory(FileReader)            #添加一个子目录

SET_PROPERTY(TARGET FileFilter  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET FileReader  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET xlnt  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET xlnt.test  PROPERTY FOLDER "CPP_Space")
SET_PROPERTY(TARGET libstudxml  PROPERTY FOLDER "CPP_Space")