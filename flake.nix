# AI generated file, i just wanted to get straight to development
# Prompt: c++ on nixos, generate a flake.nix with basic c++ development tools
{
  description = "C++ Development Environment";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          gcc
          gnumake
          cmake
          gdb
          pkg-config
        ];
      };
    };
}