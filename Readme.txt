FPD Compare Readme

;******************************************************************************;
Installation Information
;******************************************************************************;

No installer needed. Copy and paste the FPDCompare Folder to any desired place.


;******************************************************************************;
Configuration Information
;******************************************************************************;

Path of Configuration file : --xyz--/FPDCompare/Configuration/FPDCompare.ini
Details of the configuration file is described bellow

; This section is used to configure FPD Compare
; 
; Base_Path 			= Path of the FPD Directory of Base run

; Modified_Path 		= Path of the FPD Directory of Modified Run 

; Output_Path			= Path of the excel file in which the output will be generated. Mention complete path which excel file name.
;			  	  Extention shall be .xls. FYI if the excel file already exists i will be replaced.
; 
; Log_Path			= Path of the log file created by FPDCompare. Mention the extention .txt at the end
; 
; Key_Attributes		= Attribute Names of Meta File which will constitute the key. Attribute names shall be saparated by coma ','
;			  	  and no space shall be present in between them.
; 
; Ignore_List			= Attribute Names of Meta File which will be ignored during the Meta file comparasion.Attribute names shall be saparated by coma ','
;			 	  and no space shall be present in between them.
; 
; Is_Unicode			=
;					0 - if files to be parsed are not unicode files
;					1 - if files to be parsed are unicode files
;
; Enable_Meta_Comparision	=
;					0 - if complete Meta File Comparision is not desired 
;					1 - if complete Meta File Comparision is desired (Attributes in ignore list will not be matched)
; Dump_Folder_Hierarchy		=
;					0 - if dumping of Mismatch, Missing & Key Replication cases is not desired 
;					1 - if dumping of Mismatch, Missing & Key Replication cases is desired
;	
; Dump_Folder_Path		= Path of folder where dumps will be created
;
;


;******************************************************************************;
Execution Information
;******************************************************************************;
The executable is locatied at place : --xyz--/FPDCompare/Release\FPDCompare.exe

Configure the requirements in the configuration file and double click on the executable to execute.
Note: You must have rights to read and write on desired locations

;******************************************************************************;
Logging Information
;******************************************************************************;
Error logs are generated on the log file path mentioned in the configuration file
