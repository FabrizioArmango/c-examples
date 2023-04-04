echo $(pwd)

emcc Rubrica.c -o $(pwd)/test/hello.html -sEXPORTED_FUNCTIONS=_run -sEXPORTED_RUNTIME_METHODS=ccall,cwrap

docker container stop wasm-nginx
docker container rm wasm-nginx 
docker run --name wasm-nginx -v $(pwd)/test:/usr/share/nginx/html:ro -p 7000:80 -d nginx