var Chat = function(socket){
    this.socket = socket;
}
Chat.prototype.sendMessage = function(room,text){
    var message = {
        room:room,
        text:text
    };
    this.socket.emit('message',message);
}
Chat.prototype.changeRoom = function(room){
    this.socket.emit('join',{
        newRoom:room
    });
};
Chat.prototype.processCommand = function(command){
    var words = command.split(' ');
    var command = words[0]
                      .substring(1,words[0].length)
                      .toLowerCase();
    var message = false;
    switch(command){
        case 'join':
           words.shift();//将数组的第一个元素从其中删除，并返回第一个元素的值
           var room = words.join(' ');
           this.changeRoom(room);
           break;
        case 'nick':
            words.shift();
            var name = words.join(' ');
            this.socket.emit('nameAttempt',name);
            break;
        default:
            message = 'Unrecognize command.';
            break;
    }

    return message;
}