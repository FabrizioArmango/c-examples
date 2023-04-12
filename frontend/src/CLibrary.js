var CLibrary = function (opts) {
    if (opts !== undefined) {
      if (opts.imports !== undefined && opts.imports !== null) {
        if (typeof opts.imports[Symbol.iterator] === "function") {
          this.imports = opts.imports;
        } else {
          throw new Error('Invalid "imports" provided.');
        }
      }
    }
  };

  CLibrary.prototype.constructor = CLibrary;
  CLibrary.prototype.import = function () {
    var t = this;
    (this.imports || []).forEach(function (importObj) {
      t[importObj.name] = window.Module.cwrap(
        importObj.name,
        importObj.returnType,
        importObj.argumentTypes
      );
    });
  };

  export default CLibrary;