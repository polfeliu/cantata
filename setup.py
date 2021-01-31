from setuptools import setup, find_packages
from os import path

from io import open

here = path.abspath(path.dirname(__file__))

with open(path.join(here, "README.md"), encoding="utf-8") as f:
    long_description = f.read()

setup(
    name="cantata",  # Required
    version="0.0.0",  # Required
    description="Python Tool to generate C structures and functions to access candb information",  # Optional
    long_description="",  # Optional
    long_description_content_type="text/markdown",  # Optional
    url="https://github.com/polfeliu/cantata",  # Optional
    author="Pol Feliu Cuberes",  # Optional
    author_email="feliupol@gmail.com",  # Optional
    classifiers=[],  # Optional
    keywords="sample setuptools development",  # Optional
    packages=["cantata"],  # Required
    python_requires=">=2.7, !=3.0.*, !=3.1.*, !=3.2.*, !=3.3.*, !=3.4.*, <4",
    install_requires=[
        "aenum==3.0.0",
        "argparse-addons==0.6.0",
        "bitstruct==8.11.1",
        "cantools==36.2.0",
        "cogapp==3.0.0",
        "diskcache==5.2.1; python_version >= '3'",
        "python-can==3.3.4; python_version >= '2.7'",
        "textparser==0.23.0",
        "windows-curses==2.2.0",
        "wrapt==1.12.1",
    ],  # Optional
    dependency_links=[],
    project_urls={  # Optional
        "Bug Reports": "https://github.com/pypa/sampleproject/issues",
        "Funding": "https://donate.pypi.org",
        "Say Thanks!": "http://saythanks.io/to/example",
        "Source": "https://github.com/pypa/sampleproject/",
    },
)
