# Описание алгоритма работы клиента для распределённой системы подбора пароля по раскдированию файлов защищённых по схеме S63

1. При запуске клиент выполняет поиск сервера или этот поиск может быть выполнен вручную.
2. Если сервер найден, то клиент запрашивает сервер о подключении (connectionRequest);
3. Сервер подтверждает подключение (connectionConfirm) и передает клиенту размер блока для подбора ключей и первые 8 байт которые нужно расшифровывать; 
4. Получив подтверждение клиент переходит в режим ожидания команд от сервера;
5. Раз в фиксированный промежуток времени клиент проверяет подключенность к серверу (stateRequest). Если за этот промежуток времени уже было подключение к серверу для передачи данных, то запрос не выполняется, а время ожидания начинается после завершения обмена данными.
6. Находясь в режиме ожидания, клиент получает от сервера начальный ключ блока данных (transferData).
7. Клиент подтверждает (acceptData) или отказывается (refuseData) от приема данных. При отказе, сервер запрашивает состояние клиента и если клиент находится в режиме ожидания, то через определённый промежуток времени повторяет передачу начального ключа, при этом ключ может отличааться от первоначального.
8. Получив ключ выполняет подбор пароля для первых 8 байт и если в результате дешиврации получается начальная сигнатура zip-файла, то передает этот ключ серверу (transferData). Сервер подтверждает (acceptData) получения ключа. При отказе (refuseData) клиент через определенный промежуток времени повторяет передачу данных до тех пол, пока данные не будут приняты сервером. Если в результате подбора полученно несколько ключей, то они передаются последовательно;
9. После проверки всех ключей блока, клиент запрашивает новый блок ключей (transferRequest) и либо получает его или переходит в режим ожидания.
10. В любой момент может быть получен запрос состояния от сервера (stateRequest). В ответ на этот запрос клиент возвращает своё состояние (stateConfirm). 
11. Соединение между клиентом и сервером открывается только при необходимости и после завершения обмена данными закрывается.