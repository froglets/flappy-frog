from conan import ConanFile


class FlappyFrogRecipe(ConanFile):

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def configure(self):
        if self.settings.os != "Linux":
            self.options["sdl_mixer"].nativemidi = False

    @property
    def _is_desktop(self):
        return self.settings.os not in ["iOS", ]
 
    def requirements(self):
        if self._is_desktop:
            self.requires("cli11/2.1.2")
        self.requires("sdl/2.0.20")
        self.requires("sdl_image/2.0.5")
        self.requires("sdl_mixer/2.0.4")
        self.requires("box2d/2.4.1")
        self.requires("fmt/8.1.1")
        self.requires("tinkerforge-bindings/2.1.32")

        # Testing
        self.requires("catch2/2.13.7")
