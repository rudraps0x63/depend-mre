const binding = require('./binding')

class Lib {
    openLibrary(libname) {
        binding.openLibrary(libname);
    }
}

module.exports = Lib;