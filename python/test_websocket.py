import asyncio
from websockets.asyncio.server import serve

async def ReceiveHandler(websocket):
    async for message in websocket:
        print("Received: " + message + "\n")

async def SendHandler(websocket):
    while True:
        await websocket.send("123.4;567.8")
        await asyncio.sleep(2.0)

async def WebSocketHandler(websocket):
    await asyncio.gather(
        ReceiveHandler(websocket),
        SendHandler(websocket),
    )

async def main():
    async with serve(WebSocketHandler, "localhost", 8765) as server:
        await server.serve_forever()

asyncio.run(main())