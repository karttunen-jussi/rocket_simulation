def pytest_addoption(parser):
    parser.addoption("--rocket-path", action="store", help="Add path to RocketSocketServer executable")
