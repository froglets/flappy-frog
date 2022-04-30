from conan import ConanFile


class FlappyFrogRecipe(ConanFile):

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def configure(self):
        # We can control the options of our dependencies based on current options
        if self.settings.os != "Linux":
            self.options["sdl_mixer"].nativemidi = False

    def requirements(self):
        self.requires("sdl/2.0.20")
        self.requires("sdl_image/2.0.5")
        self.requires("sdl_mixer/2.0.4")
        self.requires("box2d/2.4.1")
        self.requires("cli11/2.1.2")
        self.requires("fmt/8.1.1")
        self.requires("tinkerforge-bindings/2.1.32")

        # Testing
        self.requires("catch2/2.13.7")

        # Overrides
        self.requires("zlib/1.2.12", override=True)
        self.requires("libxml2/2.9.13", override=True)
