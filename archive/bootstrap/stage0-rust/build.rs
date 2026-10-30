use std::env;

fn main() {
    println!("cargo:rerun-if-env-changed=GITHUB_ACTIONS");

    if matches!(env::var("GITHUB_ACTIONS").as_deref(), Ok("true")) {
        return;
    }

    eprintln!(
        "\nLocal Cargo builds are disabled for this repository.\n\
         Build, test, and release verification must run on GitHub Actions to protect this workstation from compiler/runtime crashes.\n\
         Push the branch or open a pull request and use the CI result as the source of truth.\n"
    );
    std::process::exit(1);
}
