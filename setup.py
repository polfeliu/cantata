from setuptools import setup, find_packages
from os import path

from io import open

here = path.abspath(path.dirname(__file__))

with open(path.join(here, "README.md"), encoding="utf-8") as f:
    long_description = f.read()

setup(
    name="python-cantata",  # Required
    version="1.2.0",  # Required
    description="Python Tool to generate C structures and functions to access candb information",  # Optional
    long_description=long_description,  # Optional
    long_description_content_type="text/markdown",  # Optional
    url="https://github.com/polfeliu/cantata",  # Optional
    author="Pol Feliu Cuberes",  # Optional
    author_email="feliupol@gmail.com",  # Optional
    classifiers=[],  # Optional
    keywords="sample setuptools development",  # Optional
    packages=["cantata"],  # Required
    python_requires=">=3",
    include_package_data=True,
    install_requires=[
        "aenum==3.0.0",
        "argparse-addons==0.7.0; python_version >= '3.6'",
        "bitstruct==8.11.1",
        "cantools==36.2.0",
        "cogapp==3.0.0",
        "cycler==0.10.0",
        "diskcache==5.2.1; python_version >= '3'",
        "kiwisolver==1.3.1; python_version >= '3.6'",
        "matplotlib==3.3.4",
        "numpy==1.20.1; python_version >= '3.7'",
        "pillow==8.1.0; python_version >= '3.6'",
        "pyparsing==2.4.7; python_version >= '2.6' and python_version not in '3.0, 3.1, 3.2'",
        "python-can==3.3.4; python_version >= '2.7'",
        "python-dateutil==2.8.1; python_version >= '2.7' and python_version not in '3.0, 3.1, 3.2'",
        "six==1.15.0; python_version >= '2.7' and python_version not in '3.0, 3.1, 3.2'",
        "textparser==0.23.0",
        "windows-curses==2.2.0",
        "wrapt==1.12.1",
    ],  # Optional
    dependency_links=[],
    project_urls={"Source": "https://github.com/polfeliu/cantata",},  # Optional
)
