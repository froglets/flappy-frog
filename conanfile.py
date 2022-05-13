from conans import ConanFile

class FlappyFrom(ConanFile):
    name = "flappy-frog"

    settings = "os", "arch", "compiler", "build_type"  # Needed for CMakeDeps
    generators = "CMakeToolchain", "CMakeDeps"

    def configure(self):
        self.options["sdl_mixer"].flac = False
        self.options["sdl_mixer"].mpg123 = False
        self.options["sdl_mixer"].mad = False
        self.options["sdl_mixer"].ogg = False
        self.options["sdl_mixer"].opus = False
        self.options["sdl_mixer"].mikmod = False
        self.options["sdl_mixer"].modplug = False
        self.options["sdl_mixer"].fluidsynth = False
        if self.settings.os != "Linux":
            self.options["sdl_mixer"].nativemidi = False
        else:
            self.options["sdl_mixer"].tinymidi = False

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
