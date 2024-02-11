/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:49:23 by psulzyck          #+#    #+#             */
/*   Updated: 2024/02/09 16:40:33 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//read new line till the \n character and concatenate it with the string 
//stored in static variable written in previous call
static char	*read_line(int fd, char *buf, char *backup)
{
    //declare variable of the data type to store the result of read()
	ssize_t		i;
    //the variable to point to the backup's pointer data for safe cancatenation of strings
	char		*char_temp;	
	i = 1;
    //the while loop which reads the file in buf variable till \n
    //concatenate the data of buf with the data of the backup 
    while (i > 0)
    {
		i = read(fd, buf, BUFFER_SIZE);
        //check for mistakes of read
		if (i == -1)
			return (0);
        //check if there is nothing to read
		else if (i == 0)
			break ;
        //null terminating buf like a string for further string manipulation operation
		buf[i] = '\0';
        //in first call of the read_line() backup points to NULL
        //we write there "" that compiler will take it like a string
		if (backup == NULL)
		{
			backup = ft_strdup("");
		}
        //make second point to data pointed by backup for safe cancatenation strings in to backup
		char_temp = backup;
        //cncatenate the data from previos read data with current data in buf
		backup = ft_strjoin(char_temp, buf);
        //free location stored data from previous call
		free(char_temp);
		char_temp = NULL;
        //break loop if we meet \n finally
		if (ft_strchr (buf, '\n'))
			break ;
	}
    //return cancatenated string to get_next_line
	return (backup);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*rest;

	count = 0;
    //let's us find the end of the line either when we encounter a \n or a \0
	while (line[count] != '\n' && line[count] != '\0')
		count++;
    //check for an empty or invalid string
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
    //create a substring starting from the character after the \n character (count + 1)
    //till the end of string
	rest = ft_substr(line, count + 1, ft_strlen(line) - count);
    //should we make a check here?
	if (rest == NULL || *rest == '\0')
	{
		free(rest);
		rest = NULL;
	}
    //null terminating a string
	line[count + 1] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
    //string where we store the data from read() till \n
	char		*line;
    //string where we store the data from one call of read() limited by buffer size
	char		*buf;
    //static variable to store the data
	static char	*backup;
    
    //check if file opened with error, buffer size is bot valid
    //and if there are mistakes during the read operation (forexample if file has no read permissions)
	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(backup);
		backup = NULL;
		return (0);
	}
    //allocate memory in heap for buf + null terminated char
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
    //call function to read new line and concatenate it with the data stored in backup
    //from previous calls of get_next_line()
	line = read_line(fd, buf, backup);
    //free buf after finishing reading
	free(buf);
    //to make buff secure
	buf = NULL;
	if (!line)
	{
		backup = NULL;
		return (NULL);
	}
    //extract the rest of the 
	backup = extract(line);
	return (line);
}
