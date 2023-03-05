import request from '../utils/request';

export const fetchData = query => {
    return request({
        url: './table.json',
        method: 'get',
        params: query
    });
};
export const AvatarData = query => {
    return request({
        url: './defaultAvatar.json',
        method: 'get',
        params: query
    });
};


export const ClassTablesData = query => {
    return request({
        url: '',
        method: 'post',
        params: query
    });
};