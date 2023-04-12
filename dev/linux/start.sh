#!/bin/bash
set -e

emcc -o addressbook.js \
    services/*.c \
    -s NO_EXIT_RUNTIME=1 \
    -s "EXPORTED_RUNTIME_METHODS=['cwrap']" \
    -s EXPORTED_FUNCTIONS="['_main', '_print_all', '_add_new', '_sort', '_update_surname']" \
    -s INCOMING_MODULE_JS_API="['ENVIRONMENT', 'GL_MAX_TEXTURE_IMAGE_UNITS', 'SDL_canPlayWithWebAudio',
  'SDL_numSimultaneouslyQueuedBuffers', 'INITIAL_MEMORY', 'wasmMemory', 'arguments',
  'buffer', 'canvas', 'doNotCaptureKeyboard', 'dynamicLibraries',
  'elementPointerLock', 'extraStackTrace', 'forcedAspectRatio',
  'instantiateWasm', 'keyboardListeningElement', 'freePreloadedMediaOnUse',
  'loadSplitModule', 'locateFile', 'logReadFiles', 'mainScriptUrlOrBlob', 'mem',
  'monitorRunDependencies', 'noExitRuntime', 'noInitialRun', 'onAbort',
  'onCustomMessage', 'onExit', 'onFree', 'onFullScreen', 'onMalloc',
  'onRealloc', 'onRuntimeInitialized', 'postMainLoop', 'postRun', 'preInit',
  'preMainLoop', 'preRun',
  'preinitializedWebGLContext', 'memoryInitializerRequest', 'preloadPlugins',
  'print', 'printErr', 'quit', 'setStatus', 'statusMessage', 'stderr',
  'stdin', 'stdout', 'thisProgram', 'wasm', 'wasmBinary', 'websocket']"

mv addressbook.wasm frontend/public/
mv addressbook.js frontend/public/

cd frontend; yarn start