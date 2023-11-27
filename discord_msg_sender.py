import discord
import asyncio

token = "MTE3Nzk3OTc3NjU2NTI0ODA1MA.GD9MYk.y_6jmLQ8o4-xVOSKvcmI6nK9phRHApEy1TnqII"

data = None  # Initialize the global variable

class MyClient(discord.Client):
    async def on_ready(self):
        print(f"Logged on as {self.user}!")
        await self.send_message("Hola! I'm ready to send messages!")
        # Schedule the hello message every 10 seconds
        self.loop.create_task(self.modify_checker())

    async def modify_checker(self):
        global data  # Add this line
        while True:
            await asyncio.sleep(20)  # Wait for 20 seconds
            with open('student_data.txt', 'r') as file:
                temp = file.read()
            if temp != data:
                data = temp
                await self.send_message("database updated")

    async def on_message(self, message):
        print(f"Message from {message.author}: {message.content}")

        if self.user != message.author and message.content == "/data":
            channel = message.channel
            with open('student_data.txt', 'r') as file:
                temp2 = file.read()
            await channel.send(temp2)

        if self.user != message.author and "/find" in message.content:
            channel = message.channel
            with open('student_data.txt', 'r') as file:
                temp3 = file.read()
            data2 = [row.split(' ') for row in temp3.split('\n')]
            index = -1
            for i in range(len(data2)-1):
                if data2[i][2] == message.content[6:]:
                    index = i
                    break
            if index != -1:
                await channel.send(' '.join(data2[index]))
            else:
                await channel.send('not found')
                
        if self.user != message.author and "/add" in message.content:
            channel = message.channel
            with open('student_data.txt', 'a') as file:
                file.write(message.content[5:] + '\n')
            await channel.send('added')
            
        if self.user != message.author and "/delete" in message.content:
            channel = message.channel
            with open('student_data.txt', 'r') as file:
                temp4 = file.read()
            data3 = [row.split(' ') for row in temp4.split('\n')]
            index = -1
            for i in range(len(data3)-1):
                if data3[i][2] == message.content[8:]:
                    index = i
                    break
            if index != -1:
                data3.pop(index)
                with open('student_data.txt', 'w') as file:
                    file.write('\n'.join([' '.join(row) for row in data3]))
                await channel.send('deleted')
            else:
                await channel.send('not found')
        
        if self.user != message.author and message.content == "/help":
            channel = message.channel
            await channel.send("Commands:\n/data\n/find <roll_num>\n/add <name> <surname> <roll_num> ....\n/delete <roll_num>")
        
    async def send_message(self, message):
        channel = discord.utils.get(self.get_all_channels(), name='general')
        if channel:
            await channel.send(message)
        else:
            print("No 'general' channel found")

intents = discord.Intents.default()
intents.message_content = True

client = MyClient(intents=intents)
client.run(token)