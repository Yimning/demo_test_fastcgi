<template>
    <div>
        <v-ClassTable :classTableData="classTableData" />
    </div>
</template>
<script>
var that;
import ClassTable from '../../components/ClassTable';
//import { reqFindTeacherLesson } from '../../config/api';
export default {
    data() {
        return {
            msg: '',
            classTableData: {
                weeks: ['', '一', '二', '三', '四', '五', '六', '日'],
                num: ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12'],
                courses: [
                    {  
                        id: 1,
                        classId: 2,
                        lessonsTime: '8:00-9:40',
                        lessonsName: '计算机导论',
                        lessonsAddress: '二教302',
                        lessonsTeacher: '吴老师',
                        lessonsRemark: '1-17周',
                        lessonsNumber: '一',
                        weekday: '星期一'
                    },
                    {
                        id: 4,
                        classId: 2,
                        lessonsTime: '8:00-9:40',
                        lessonsName: '编译原理',
                        lessonsAddress: '二教302',
                        lessonsTeacher: '吴老师',
                        lessonsRemark: '1-5,8-12周',
                        lessonsNumber: '四',
                        weekday: '星期四'
                    },
                    {
                        id: 4,
                        classId: 2,
                        lessonsTime: '8:00-9:40',
                        lessonsName: '编译原理',
                        lessonsAddress: '二教302',
                        lessonsTeacher: '吴老师',
                        lessonsRemark: '1-5,8-12周',
                        lessonsNumber: '四',
                        weekday: '星期四'
                    }
                ]
            }
        };
    },
    components: {
        'v-ClassTable': ClassTable
    },
    created() {
        // const { userId, userName, roleId } = JSON.parse(this.$cookie.get('userInfo'));
        // this.findTeacherLesson(userName);
    },
    methods: {
        // // 查询教师课表
        // async findTeacherLesson(userName) {
        //     that = this;
        //     var params = {
        //         userName: userName
        //     };
        //     const { msg, status, info } = await reqFindTeacherLesson(params);
        //     that.classTableData.courses = info;
        // }
    }
};
</script>
