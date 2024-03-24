# TRPO_Lab_1.1
## Задача
Создать консольное приложение для отслеживания изменений файлов.
Пользователь может добавлять и удалять файлы из списка прослушиваемых. 

### Характеристики файла
1. Файл существует.
2. Размер файла.

### Уведомления об изменениях
1. Если файл существует, файл не пустой - выводится: exist true и file size
2. Если файл существует, файл был изменен - выводится: exist true, file size, file Modifier, date Last Modifier.
3. Если файл не существует - выводится: exist false

## Архитектура
1. MyApplication : QApplication осуществляет прослушку консольных команд, обновление статуса FileManager, контроль сигнально-слотового соединения между FileManager и Loger
2. <Singleton> FileManager контролирует список FileInfoRecorder, обрабатывает обновления FileInfoRecorder
3. FileInfoRecorder : QFileInfo запоминает, обновляет характеристики файла и отправляет сигнал об изменениях в FileManager
4. <Singleton> Loger выводит уведомления в консоль об изменениях файла.

## UML-диаграмма
![Иллюстрация к проекту](https://github.com/Ran00dom/TRPO_Lab_1.1/raw//task_description/UML-класс_7.png)

