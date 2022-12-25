# Simple Docker
## Part 1. Готовый докер

##### Взять официальный докер образ с **nginx** и выкачать его при помощи `docker pull`

- ![part-1-1](/misc/images/docker1-1.png)

##### Проверить наличие докер образа через `docker images`

- ![part-1-2](/misc/images/docker1-2.png)

##### Запустить докер образ через `docker run -d [image_id|repository]`

- ![part-1-3](/misc/images/docker1-3.png)

##### Проверить, что образ запустился через `docker ps`

- ![part-1-4](/misc/images/docker1-4.png)

##### Посмотреть информацию о контейнере через `docker inspect [container_id|container_name]`
##### По выводу команды определить и поместить в отчёт размер контейнера, список замапленных портов и ip контейнера

- ![part-1-fix](/misc/images/docker-fix-1.png)

|   |   |
|---|---|
| ShmSize | 67108864 бит |
| Ports | 80/tcp |
| IPAddress | 172.17.0.2 |

##### Остановить докер образ через `docker stop [container_id|container_name]`

- ![part-1-6](/misc/images/docker1-6.png)

##### Проверить, что образ остановился через `docker ps`

- ![part-1-7](/misc/images/docker1-7.png)

##### Запустить докер с замапленными портами 80 и 443 на локальную машину через команду *run*

- ![part-1-8](/misc/images/docker1-8.png)

##### Проверить, что в браузере по адресу *localhost:80* доступна стартовая страница **nginx**

- ![part-1-9](/misc/images/docker1-9.png)
- ![part-1-9+](/misc/images/docker1-9+.png)

##### Перезапустить докер контейнер через `docker restart [container_id|container_name]`
##### Проверить любым способом, что контейнер запустился

- ![part-1-10](/misc/images/docker1-10.png)



## Part 2. Операции с контейнером

##### Прочитать конфигурационный файл *nginx.conf* внутри докер контейнера через команду *exec*

- ![part-2-1](/misc/images/docker2-1.png)

##### Создать на локальной машине файл *nginx.conf*
##### Настроить в нем по пути */status* отдачу страницы статуса сервера **nginx**

- ![part-2-2](/misc/images/docker2-2.png)

##### Скопировать созданный файл *nginx.conf* внутрь докер образа через команду `docker cp`

- ![part-2-3](/misc/images/docker2-3.png)

##### Перезапустить **nginx** внутри докер образа через команду *exec*

- ![part-2-4](/misc/images/docker2-4.png)

##### Проверить, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**

- ![part-2-5](/misc/images/docker2-5.png)

##### Экспортировать контейнер в файл *container.tar* через команду *export*

- ![part-2-6](/misc/images/docker2-6.png)

##### Остановить контейнер

- ![part-2-7](/misc/images/docker2-7.png)

##### Удалить образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры
##### Удалить остановленный контейнер

- ![part-2-fix](/misc/images/docker-fix-2.png)

##### Импортировать контейнер обратно через команду *import*
##### Запустить импортированный контейнер
##### Проверить, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**

- ![part-2-9](/misc/images/docker2-9.png)
- ![part-2-10](/misc/images/docker2-10.png)


## Part 3. Мини веб-сервер

##### Написать мини сервер на **C** и **FastCgi**, который будет возвращать простейшую страничку с надписью `Hello World!`

- ![part-3-1](/misc/images/docker3-1.png)

##### Запустить написанный мини сервер через *spawn-fcgi* на порту 8080

- ![part-3-2](/misc/images/docker3-2.png)

##### Написать свой *nginx.conf*, который будет проксировать все запросы с 81 порта на *127.0.0.1:8080*

- ![part-3-3](/misc/images/docker3-3.png)

##### Проверить, что в браузере по *localhost:81* отдается написанная вами страничка

- ![part-3-4](/misc/images/docker3-4.png)


## Part 4. Свой докер

#### Написать свой докер образ, который:
##### 1) собирает исходники мини сервера на FastCgi из [Части 3](#part-3-мини-веб-сервер)
##### 2) запускает его на 8080 порту
##### 3) копирует внутрь образа написанный *./nginx/nginx.conf*
##### 4) запускает **nginx**.

- ![part-4-1](/misc/images/docker4-1.png)

##### Собрать написанный докер образ через `docker build` при этом указав имя и тег
##### Проверить через `docker images`, что все собралось корректно
##### Запустить собранный докер образ с маппингом 81 порта на 80 на локальной машине и маппингом папки *./nginx* внутрь контейнера по адресу, где лежат конфигурационные файлы **nginx**
##### Проверить, что по localhost:80 доступна страничка написанного мини сервера

- ![part-4-2](/misc/images/docker4-2.png)

##### Дописать в *./nginx/nginx.conf* проксирование странички */status*, по которой надо отдавать статус сервера **nginx**

- ![part-4-3](/misc/images/docker4-3.png)

##### Перезапустить докер образ
##### Проверить, что теперь по *localhost:80/status* отдается страничка со статусом **nginx**

- ![part-4-4](/misc/images/docker4-4.png)


## Part 5. **Dockle**

##### Просканировать образ из предыдущего задания через `dockle [image_id|repository]`
##### Исправить образ так, чтобы при проверке через **dockle** не было ошибок и предупреждений

- ![part-5-1](/misc/images/docker5-1.png)

- ![part-5-2](/misc/images/docker5-2.png)

- Игнорим не **warning** и не **fatal error** с помощью флага -i (--ignore)
- Флаг -ak (acccept-key) убирает ошибку где Dockle жалуется на ключ из образа nginx (FROM nginx)
- ![part-5-3](/misc/images/docker5-3.png)

## Part 6. Базовый **Docker Compose**

##### Написать файл *docker-compose.yml*, с помощью которого:
##### 1) Поднять докер контейнер из [Части 5](#part-5-инструмент-dockle)
##### 2) Поднять докер контейнер с **nginx**, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера
##### Замапить 8080 порт второго контейнера на 80 порт локальной машины

- ![part-6-1](/misc/images/docker6-1.png)
- ![part-6-2](/misc/images/docker6-2.png)

##### Собрать и запустить проект с помощью команд `docker-compose build` и `docker-compose up`
##### Проверить, что в браузере по *localhost:80* отдается написанная вами страничка, как и ранее

- ![part-6-3](/misc/images/docker6-3.png)