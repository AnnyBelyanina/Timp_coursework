#!/bin/bash

LOG='test.log'
SERVER='./vcalc_server'
CLIENT='./client_double'

# Очистка старого лога
> $LOG

echo '==========================' >> $LOG
echo 'Функциональное тестирование vcalc_server' >> $LOG
echo '==========================' >> $LOG

# Тест 1: Справка без параметров
echo '' >> $LOG
echo 'Тест 1: Вывод справки без параметров' >> $LOG
$SERVER >> $LOG 2>&1
echo 'Код возврата: '$? >> $LOG

# Тест 2: Справка -h
echo '' >> $LOG
echo 'Тест 2: Вывод справки с ключом -h' >> $LOG
$SERVER -h >> $LOG 2>&1
echo 'Код возврата: '$? >> $LOG

# Тест 3: Неверный параметр
echo '' >> $LOG
echo 'Тест 3: Неверный параметр' >> $LOG
$SERVER --run -x 2>> $LOG
echo 'Код возврата: '$? >> $LOG

# Тест 4: Отсутствие файла БД
echo '' >> $LOG
echo 'Тест 4: Отсутствие файла БД' >> $LOG
$SERVER --run -d notfound.conf 2>> $LOG
echo 'Код возврата: '$? >> $LOG

# Тест 5: Создание файла журнала
echo '' >> $LOG
echo 'Тест 5: Создание файла журнала' >> $LOG
rm -f test_run.log
$SERVER --run -l test_run.log &
PID=$!
sleep 2
kill $PID 2>/dev/null
if [ -f "test_run.log" ]; then
    echo 'Файл журнала создан' >> $LOG
    cat test_run.log >> $LOG
else
    echo 'ОШИБКА: Файл журнала не создан' >> $LOG
fi
rm -f test_run.log

# Тест 6: Устойчивость (20 запусков)
echo '' >> $LOG
echo 'Тест 6: Тестирование устойчивости (20 запусков)' >> $LOG
SUCCESS=0
for i in $(seq 1 20); do
    $SERVER --run -p 44444 -l stability_$i.log &
    PID=$!
    sleep 1
    if kill -0 $PID 2>/dev/null; then
        SUCCESS=$((SUCCESS+1))
    fi
    kill $PID 2>/dev/null
    rm -f stability_$i.log
done
echo "Сервер успешно запущен $SUCCESS раз из 20" >> $LOG
if [ $SUCCESS -eq 20 ]; then
    echo 'Тест устойчивости пройден' >> $LOG
else
    echo 'ОШИБКА: Сервер не прошёл тест устойчивости' >> $LOG
fi

# Тест 7: Нагрузочное тестирование (10 клиентов)
echo '' >> $LOG
echo 'Тест 7: Нагрузочное тестирование (10 клиентов)' >> $LOG

# Запускаем сервер в фоне на порту 33333
$SERVER --run -p 33333 -l load.log &
SERVER_PID=$!
sleep 2

# Запускаем 10 клиентов одновременно
for i in $(seq 1 10); do
    $CLIENT -H SHA256 -S client &
done

# Ждем завершения клиентов (даём им время на аутентификацию и обмен)
sleep 10

# Проверяем, что сервер всё ещё работает
if kill -0 $SERVER_PID 2>/dev/null; then
    echo 'Сервер продолжает работать после 10 подключений' >> $LOG
    echo 'Записей в журнале load.log:' >> $LOG
    cat load.log >> $LOG
else
    echo 'ОШИБКА: Сервер завершил работу' >> $LOG
fi

kill $SERVER_PID 2>/dev/null
rm -f load.log

echo '' >> $LOG
echo '==========================' >> $LOG
echo 'Тестирование завершено' >> $LOG
