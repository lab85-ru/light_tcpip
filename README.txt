Проект Легкий TCP/IP стек.
Компилятор IAR ARM 6.50(win7)
Отладчик ST-LINK(discovery-stm32).


			Проект Легкий TCP/IP стек.
Сейчас реализовано:

Вывод отладки в консоль 115200 8N1.







это мусор пока...
//*****************************************************************
//	TEMPLATE FOR STM32F10xx
//	
//	Includes: 						- IAR 6.30 demo project
//											- CMSIS library
//											- STM32F10x Library V3.5.0
// 											- FreeRTOS 7.1.0
//
//	Author:							Cyber Genius
//	Date:								20.02.2012
//	
//	Template version:			1.0.0
//*****************************************************************

Чтобы изменить название проекта:

	- изменить имя следующих файлов на произвольное:
	project.dep			->		MY_PROJECT_NAME.dep
	project.ewd			->		MY_PROJECT_NAME.ewd
	project.ewp			->		MY_PROJECT_NAME.ewp	
	project.eww		->		MY_PROJECT_NAME.eww

	- открыть текстовым редактором файл project.eww и изменить строчку <path>$WS_DIR$\project.ewp</path>
	на например такой <path>$WS_DIR$\MY_PROJECT_NAME.ewp</path>
